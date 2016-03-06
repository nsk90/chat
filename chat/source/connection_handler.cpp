#include "connection_handler.h"

#include <stdexcept>
#include <QDataStream>

#include "criptographer_xor.h"

namespace {
///
/// \brief заголовок сообщения
///
struct MessageHeader
{
    MessageHeader():
        m_id( 0 )
    {}
    qint32 m_id;///< иденификатор сообщения
};

QDataStream & operator <<( QDataStream & stream, const MessageHeader & data )
{
    return stream << data.m_id;
}

QDataStream & operator >>( QDataStream & stream, MessageHeader & data )
{
    return stream >> data.m_id;
}

} //namespace

QDataStream & operator <<( QDataStream & stream, const PingMessage & data )
{
    return stream << data.m_nick_name;
}

QDataStream & operator >>( QDataStream & stream, PingMessage & data )
{
    return stream >> data.m_nick_name;
}

ConnectionHandler::ConnectionHandler()
{
    setupConnections();
    //привяжемся куда попало
    m_socket.bind();
    if( m_ping_timer )
        m_ping_timer->start( 3000 );//время пингов
}

ConnectionHandler::~ConnectionHandler()
{
}

void ConnectionHandler::writeMessage( NetworkMessage id,
                                      const QByteArray & data,
                                      const QHostAddress & adress,
                                      quint32 port )
{
    MessageHeader header;
    header.m_id = id;

    QByteArray buffer;
    QDataStream stream( &buffer, QIODevice::WriteOnly );
    stream << header << data;
    m_socket.writeDatagram( buffer, adress, port );
}

void ConnectionHandler::onSocketReadyRead()
{
    while( m_socket.hasPendingDatagrams() )
    {
        QByteArray buffer( m_socket.pendingDatagramSize(), '0');
        QHostAddress adress;
        quint16 port = 0;
        if( -1 != m_socket.readDatagram( buffer.data(), buffer.size(), &adress, &port ) )
        {
            CriptographerXOR criptographer;
            readMessage( criptographer.decode( buffer ), adress, port );
        }
        else
            qDebug() << "ConnectionHandler::onSocketReadyRead reading datagram error";
    }
}

void ConnectionHandler::onPingTimerTimeout()
{
    PingMessage data;
    data.m_nick_name = "test";//TODO

    QByteArray buffer;
    QDataStream stream( &buffer, QIODevice::WriteOnly );
    stream << data;
    writeMessage( NetworkMessagePing, buffer, QHostAddress::Broadcast, 0 );
}

void ConnectionHandler::setupConnections()
{
    connect( &m_socket, &QUdpSocket::readyRead,
             this, &ConnectionHandler::onSocketReadyRead );

    m_ping_timer.reset( new QTimer );
    connect( m_ping_timer.data(), &QTimer::timeout,
             this, &ConnectionHandler::onPingTimerTimeout );
}

void ConnectionHandler::readMessage( const QByteArray & message, const QHostAddress & adress, quint32 port )
{
    QDataStream stream( message );
    //читаем шапку
    MessageHeader header;
    stream >> header;
    switch ( header.m_id )
    {
        case NetworkMessagePing:
        {
            PingMessage data;
            stream >> data;
            if( QDataStream::Ok == stream.status() )
                emit receivedPing( data, adress, port );
            else
                qDebug() << "ConnectionHandler::readMessage error";
        } break;
        case NetworkMessageData:
        {
            QByteArray data;
            stream >> data;
            if( QDataStream::Ok == stream.status() )
                emit receivedData( data, adress, port );
            else
                qDebug() << "ConnectionHandler::readMessage error";
        } break;
        default:
            qDebug() << "ConnectionHandler::readMessage unknown message";
        break;
    }
}


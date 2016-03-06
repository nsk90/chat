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

///
/// \brief структура передается в сообщении NetworkMessagePing
///
struct PingMessage
{
    QString m_nick_name;
};


} //namespace

ConnectionHandler::ConnectionHandler()
{
    setupConnections();
    //привяжемся куда попало
    m_socket.bind();
    if( m_ping_timer )
        m_ping_timer->start( 2000 );//время пингов
}

ConnectionHandler::~ConnectionHandler()
{
}

void ConnectionHandler::writeMessage( NetworkMessage id, QByteArray data, const QHostAddress & adress, quint32 port )
{
    MessageHeader header;
    header.m_id = id;

    QByteArray buffer;
    QDataStream stream( &buffer, QIODevice::WriteOnly );
    stream >> header >> data;
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

void ConnectionHandler::onPingTimerTimeeout()
{
    writeMessage( NetworkMessagePing, );
}

void ConnectionHandler::setupConnections()
{
    connect( &m_socket, &QUdpSocket::readyRead,
             this, &ConnectionHandler::onSocketReadyRead );

    m_ping_timer.reset( new QTimer );
    connect( m_ping_timer.data(), &QTimer::timeout,
             this, &ConnectionHandler::onPingTimerTimeeout );
}

void ConnectionHandler::readMessage( const QByteArray & message, const QHostAddress & adress, quint32 port )
{
    QDataStream stream( message );
    //читаем шапку
    MessageHeader header;
    stream << header;
    if( QDataStream::Ok == stream.status() )
        switch ( header.m_id )
        {
            case NetworkMessagePing:
            {
                QByteArray data;
                stream << data;
                QString nick( data );
                emit receivedPing( nick );
            } break;
            case NetworkMessageData:
            {
                QString text;
                stream << text;

            } break;
            default:
                qDebug() << "ConnectionHandler::readMessage unknown message";
            break;
        }

    stream << data;

}


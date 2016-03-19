#include "connection_handler.h"

#include <stdexcept>
#include <QDataStream>
#include <QNetworkInterface>

#include "network_structs.h"
#include "criptographer_xor.h"

namespace {
quint32 cChatPort = 555;//TODO порт привязки любой или нет?
} //namespace

ConnectionHandler::ConnectionHandler( QObject * parent ) :
    QObject( parent )
{
    setupConnections();
    //привяжемся куда попало
    m_socket.bind( cChatPort );
    if( m_pingTimer )
        m_pingTimer->start( 3000 );//время пингов
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
    stream.setVersion( QDataStream::Qt_5_5 );

    stream << header << data;

    CriptographerXOR criptographer;
    m_socket.writeDatagram( criptographer.encode( buffer ), adress, port );
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
            //TODO не надо обрабатывать сообщения от себя?
            {
                CriptographerXOR criptographer;
                readMessage( criptographer.decode( buffer ), adress, port );
            }
        }
        else
            qDebug() << "ConnectionHandler::onSocketReadyRead reading datagram error";
    }
}

void ConnectionHandler::onPingTimerTimeout()
{
    PingMessage data;
    data.m_nickName = "test";//TODO

    QByteArray buffer;
    QDataStream stream( &buffer, QIODevice::WriteOnly );
    stream.setVersion( QDataStream::Qt_5_5 );

    stream << data;

    writeMessage( NetworkMessagePing, buffer,
                  QHostAddress::Broadcast, cChatPort );
}

void ConnectionHandler::setupConnections()
{
    connect( &m_socket, &QUdpSocket::readyRead,
             this, &ConnectionHandler::onSocketReadyRead );

    m_pingTimer.reset( new QTimer );
    connect( m_pingTimer.data(), &QTimer::timeout,
             this, &ConnectionHandler::onPingTimerTimeout );
}

void ConnectionHandler::readMessage( const QByteArray & message, const QHostAddress & adress, quint32 port )
{
    QDataStream stream( message );
    stream.setVersion( QDataStream::Qt_5_5 );

    //читаем шапку
    MessageHeader header;
    stream >> header;
    if( QDataStream::Ok == stream.status() )
    {
        switch ( header.m_id )
        {
            case NetworkMessagePing:
            {
                QByteArray data;
                stream >> data;
                if( QDataStream::Ok == stream.status() )
                    readPingMessage( data, adress, port );
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
    else
        qDebug() << "ConnectionHandler::readMessage read header error";
}

void ConnectionHandler::readPingMessage( const QByteArray & data, const QHostAddress & adress, quint32 port )
{
    QDataStream stream( data );
    stream.setVersion( QDataStream::Qt_5_5 );

    PingMessage ping;
    stream >> ping;
    if( QDataStream::Ok == stream.status() )
        emit receivedPing( ping, adress, port );
    else
        qDebug() << "ConnectionHandler::readPingMessage read error";
}


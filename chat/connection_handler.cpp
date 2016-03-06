#include "connection_handler.h"

ConnectionHandler::ConnectionHandler()
{
    connectToSocket();
}

ConnectionHandler::~ConnectionHandler()
{

}

void ConnectionHandler::onSocketReadyRead()
{
    while( m_socket.hasPendingDatagrams() )
    {
        QByteArray buffer( udpSocket->pendingDatagramSize(), '0');
        QHostAddress adress;
        quint16 port = 0;
        if( -1 != m_socket.readDatagram( buffer.data(), buffer.size(), &adress, &port ) )
        {
            //читаем шапку

        }
        else
            qDebug() << "ConnectionHandler::onSocketReadyRead reading datagram error";
    }
}

void ConnectionHandler::connectToSocket()
{
    connect( m_socket, &QUdpSocket::readyRead,
             this, &ConnectionHandler::onSocketReadyRead );
}


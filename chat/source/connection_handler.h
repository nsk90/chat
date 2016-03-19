#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <QUdpSocket>
#include <QTimer>
#include <QSharedPointer>

#include "enums.h"

struct PingMessage;
///
/// \brief Обработчик сетевого взаимодействия
///
class ConnectionHandler :
    public QObject
{
    Q_OBJECT
public:
    explicit ConnectionHandler( QObject * parent = 0 );
    virtual ~ConnectionHandler();
    /// \brief отправляет сообщение
    ///
    /// дынные упаковываются по протоколу приложени и шифруются
    void writeMessage( NetworkMessage id,
                       const QByteArray & data,
                       const QHostAddress & adress,
                       quint32 port );
signals:
    void receivedPing( const PingMessage & data, const QHostAddress & adress, quint32 port );
    void receivedData( const QByteArray & data, const QHostAddress & adress, quint32 port );
private slots:
    void onSocketReadyRead();
    void onPingTimerTimeout();
private:
    void setupConnections();
    void readMessage( const QByteArray & message, const QHostAddress & adress, quint32 port );
    /// \brief читает из полученный данных структуру PingMessage
    void readPingMessage( const QByteArray & data, const QHostAddress & adress, quint32 port );

    QUdpSocket m_socket;
    QSharedPointer< QTimer > m_pingTimer;

};

#endif // CONNECTION_HANDLER_H

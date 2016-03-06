#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <QUdpSocket>
#include <QTimer>
#include <QSharedPointer>

///
/// \brief идентификаторы сетевых сообщений
///
enum NetworkMessage
{
    NetworkMessagePing,///< сообщение посылается для поддержания свзяи между клиентами
    NetworkMessageData,///< сообщение с информацией
};
///
/// \brief Обработчик сетевого взаимодействия
///
class ConnectionHandler :
    public QObject
{
    Q_OBJECT
public:
    ConnectionHandler();
    virtual ~ConnectionHandler();

    /// \brief отправляет сообщение
    ///
    /// дынные упаковываются по протоколу приложени и шифруются
    void writeMessage( NetworkMessage id, QByteArray data, const QHostAddress & adress, quint32 port );
signals:
    void receivedPing();
    void receivedData();
private slots:
    void onSocketReadyRead();
    void onPingTimerTimeeout();
private:
    void setupConnections();
    void readMessage( const QByteArray & message, const QHostAddress & adress, quint32 port );

    QUdpSocket m_socket;
    QSharedPointer< QTimer > m_ping_timer;

};

#endif // CONNECTION_HANDLER_H

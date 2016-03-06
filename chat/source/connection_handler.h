#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <QUdpSocket>

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
signals:

private slots:
    void onSocketReadyRead();
private:
    void connectToSocket();

    QUdpSocket m_socket;
};

#endif // CONNECTION_HANDLER_H

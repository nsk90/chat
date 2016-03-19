#ifndef APP_MODEL_H
#define APP_MODEL_H

#include <QObject>

#include "connection_handler.h"
#include "clients_list_model.h"
///
/// \brief основная модель приложения ( синглтон )
///
class AppModel :
    public QObject
{
    Q_OBJECT
public:
    explicit AppModel( QObject * parent = 0 );
    virtual ~AppModel();

    static AppModel & instance();
    ConnectionHandler & connectionHandler() { return m_connectionHandler; }
    const ConnectionHandler & connectionHandler() const { return m_connectionHandler; }
signals:

public slots:
private:
    void InitialiseNetwork();

    ClientsListModel m_clientsModel;
    ConnectionHandler m_connectionHandler;
};

#endif // APP_MODEL_H

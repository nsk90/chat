#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QHostAddress>
///
/// \brief модель клиента
///
class ClientModel :
    public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer< ClientModel > Shared;
    explicit ClientModel( QObject * parent = 0 );

    const QString & nickName() const { return m_nickName; }
    void SetNickName( const QString & nick );
signals:
    void nickNameChanged( const QString & nick );
public slots:
private:
    QString m_nickName;
    QHostAddress m_adress;
    quint32 m_port;
};

#endif // CLIENTMODEL_H

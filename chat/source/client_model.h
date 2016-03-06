#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>
#include <QSharedPointer>
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

    const QString & nickName() const { return m_nick_name; }
signals:

public slots:
private:
    QString m_nick_name;
};

#endif // CLIENTMODEL_H

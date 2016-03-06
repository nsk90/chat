#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>
///
/// \brief модель клиента
///
class ClientModel :
    public QObject
{
    Q_OBJECT
public:
    explicit ClientModel( QObject * parent = 0 );

    const QString & nickName() const { return m_nick_name; }
signals:

public slots:
private:
    QString m_nick_name;
};

#endif // CLIENTMODEL_H

#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>

///
/// \brief основная модель приложения
///
class AppModel :
    public QObject
{
    Q_OBJECT
public:
    explicit AppModel( QObject * parent = 0 );

signals:

public slots:
};

#endif // APPMODEL_H

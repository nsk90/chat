#include "app_model.h"

#include <QAtomicPointer>


namespace {
//синглтонизирую модель так - чтобы время жизни объекта было НЕ статическим,
//т.к. для это может быть проблемой
QAtomicPointer< AppModel > appInstancePtr = 0;
} //namespace

AppModel::AppModel( QObject * parent ) :
    QObject( parent )
{
    Q_ASSERT( appInstancePtr == 0 );
    appInstancePtr = this;
}

AppModel::~AppModel()
{
    Q_ASSERT( appInstancePtr );
    appInstancePtr = 0;
}

AppModel & AppModel::instance()
{
    Q_ASSERT( appInstancePtr );
    return *appInstancePtr;
}

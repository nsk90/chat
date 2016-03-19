#include "client_model.h"

ClientModel::ClientModel( QObject * parent ) :
    QObject( parent )
{

}

void ClientModel::SetNickName( const QString & nick )
{
    if( m_nickName != nick )
    {
        m_nickName = nick;
        emit nickNameChanged( m_nickName );
    }
}


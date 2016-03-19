#include "clients_list_model.h"

ClientsListModel::ClientsListModel( QObject * parent ) :
    QAbstractListModel( parent )
{

}

void ClientsListModel::reset()
{
    beginResetModel();
    foreach ( ClientModel::Shared client, m_clients )
        disconnectFromClient( client );
    m_clients.clear();
    endResetModel();
}

void ClientsListModel::addClient( ClientModel::Shared client )
{
    if( client )
    {
        beginInsertRows( QModelIndex(), m_clients.size(), m_clients.size() );
        connectToClient( client );
        m_clients.push_back( client );
        endInsertRows();
    }
}

void ClientsListModel::removeClient( ClientModel::Shared client )
{
    int pos = m_clients.indexOf( client );
    if( -1 != pos )
    {
        beginRemoveRows( QModelIndex(), pos, pos );
        disconnectFromClient( client );
        m_clients.removeAt( pos );
        endRemoveRows();
    }
}

int ClientsListModel::rowCount( const QModelIndex & parent ) const
{
    return m_clients.size();
}

QVariant ClientsListModel::data( const QModelIndex & index, int role ) const
{
    QVariant result;
    if( index.isValid() ||
        index.row() <= m_clients.size() )
        switch ( role )
        {
            case Qt::DisplayRole:
                if( m_clients[ index.row() ] )
                    result = m_clients[ index.row() ]->nickName();
            break;
        }
    return result;
}

void ClientsListModel::onClientDataChanged()
{
    if( ClientsListModel * client = qobject_cast< ClientsListModel * >( sender() ) )
    {
        //TODO
        QModelIndex index;// = createIndex( m_clients.indexOf( client ), 0 );
        emit dataChanged( index, index );
    }
}

void ClientsListModel::connectToClient( ClientModel::Shared client )
{
    if( client )
        connect( client.data(), &ClientModel::nickNameChanged,
                 this, &ClientsListModel::onClientDataChanged );
}

void ClientsListModel::disconnectFromClient( ClientModel::Shared client )
{
    if( client )
        client->disconnect( this );
}


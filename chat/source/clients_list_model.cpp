#include "clients_list_model.h"

ClientsListModel::ClientsListModel( QObject * parent ) :
    QAbstractListModel( parent )
{

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


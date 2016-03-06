#ifndef CLIENTSLISTMODEL_H
#define CLIENTSLISTMODEL_H

#include <QAbstractListModel>

#include "client_model.h"

///
/// \brief модель списка клиентов
///
class ClientsListModel :
    public QAbstractListModel
{
public:
    explicit ClientsListModel( QObject * parent = 0 );

    virtual int rowCount( const QModelIndex &parent = QModelIndex() ) const Q_DECL_OVERRIDE;
    virtual QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE;
private:
    QList< ClientModel::Shared > m_clients;
};

#endif // CLIENTSLISTMODEL_H

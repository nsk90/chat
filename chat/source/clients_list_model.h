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
    Q_OBJECT
public:
    explicit ClientsListModel( QObject * parent = 0 );

    void reset();
    void addClient( ClientModel::Shared client );
    void removeClient( ClientModel::Shared client );

    virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const Q_DECL_OVERRIDE;
    virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE;
private slots:
    void onClientDataChanged();
private:
    void connectToClient( ClientModel::Shared client );
    void disconnectFromClient( ClientModel::Shared client );
    QList< ClientModel::Shared > m_clients;
};

#endif // CLIENTSLISTMODEL_H

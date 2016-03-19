#ifndef NETWORK_STRUCTS_H
#define NETWORK_STRUCTS_H

#include <QDataStream>

///
/// \brief заголовок сообщения
///
struct MessageHeader
{
    MessageHeader():
        m_id( 0 )
    {}
    qint32 m_id;///< иденификатор сообщения
};

QDataStream & operator <<( QDataStream & stream, const MessageHeader & data );
QDataStream & operator >>( QDataStream & stream, MessageHeader & data );

///
/// \brief структура передается в сообщении NetworkMessagePing
///
struct PingMessage
{
    QString m_nickName;
};

QDataStream & operator <<( QDataStream & stream, const PingMessage & data );
QDataStream & operator >>( QDataStream & stream, PingMessage & data );



#endif // NETWORK_STRUCTS_H

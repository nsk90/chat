#include "network_structs.h"


QDataStream & operator <<( QDataStream & stream, const MessageHeader & data )
{
    return stream << data.m_id;
}

QDataStream & operator >>( QDataStream & stream, MessageHeader & data )
{
    return stream >> data.m_id;
}

QDataStream & operator <<( QDataStream & stream, const PingMessage & data )
{
    return stream << data.m_nickName;
}

QDataStream & operator >>( QDataStream & stream, PingMessage & data )
{
    return stream >> data.m_nickName;
}

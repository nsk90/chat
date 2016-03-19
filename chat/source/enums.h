#ifndef ENUMS_H
#define ENUMS_H

///
/// \brief идентификаторы сетевых сообщений
///
enum NetworkMessage
{
    NetworkMessagePing = 1,///< сообщение посылается для поддержания свзяи между клиентами
    NetworkMessageData,///< сообщение с информацией
};

#endif // ENUMS_H


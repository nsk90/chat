#ifndef CRIPTOGRAPHERXOR_H
#define CRIPTOGRAPHERXOR_H

#include <QString>
///
/// \brief шифрует / дешифрует  данные по известному ключу (паролю)
///
class CriptographerXOR
{
public:
    CriptographerXOR();

    const QString & password() const { return m_password; }

    QByteArray encode( const QByteArray & data );
    QByteArray decode( const QByteArray & data );
private:
    Q_DISABLE_COPY(CriptographerXOR)

    QString m_password;
};

#endif // CRIPTOGRAPHERXOR_H

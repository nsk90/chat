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

    const QByteArray & password() const { return m_password; }

    /// \brief зашифрует данные
    QByteArray encode( const QByteArray & data ) const { return xORdataByPassword( data ); }
    /// \brief расшифрует данные
    QByteArray decode( const QByteArray & encodedData ) const { return xORdataByPassword( encodedData ); }
private:
    Q_DISABLE_COPY(CriptographerXOR)
    QByteArray xORdataByPassword( QByteArray data ) const;

    const QByteArray m_password;
};

#endif // CRIPTOGRAPHERXOR_H

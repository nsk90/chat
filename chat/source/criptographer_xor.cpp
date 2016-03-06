#include "criptographer_xor.h"

CriptographerXOR::CriptographerXOR() :
    m_password( "thisIsVeryStrongPassword" )
{
}

QByteArray CriptographerXOR::xORdataByPassword( QByteArray data ) const
{
    for ( int i = 0; i < data.size(); ++i )
        data[i] = data[i] ^ m_password[ i % m_password.size() ];
    return data;
}


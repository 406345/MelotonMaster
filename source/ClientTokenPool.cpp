#include <ClientTokenPool.h>
#include <MRT.h>

string ClientTokenPool::CreateToken( size_t clientId )
{
    sptr<ClientToken> token = make_sptr( ClientToken , MRT::UUID::Create() , clientId );
    this->Push( token );
}

bool ClientTokenPool::RemoveToken( string token )
{
    auto t = this->Find( [&token] ( sptr<ClientToken> clientToken ) { 
        if ( clientToken->Token() == token )
        {
            return clientToken;
        }
    } );

    this->Pop( t );

    return false;
}

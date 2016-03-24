#include <ClientTokenPool.h>
#include <MRT.h>

sptr<ClientToken> ClientTokenPool::CreateToken( size_t clientId )
{
    sptr<ClientToken> token = make_sptr( ClientToken , "" , MRT::UUID::Create() , clientId );
    this->Push( token );
    return token;
}

bool ClientTokenPool::RemoveToken( string token )
{
    auto t = this->Find( [&token] ( sptr<ClientToken> clientToken ) { 
        return  clientToken->Token() == token ;
    } );

    this->Pop( t );

    return false;
} 

sptr<ClientToken> ClientTokenPool::CheckToken( string token )
{
    auto t = this->Find( [&token] ( sptr<ClientToken> clientToken ) { 
        return  clientToken->Token() == token ;
    } );

    return t;
} 
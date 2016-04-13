#include <ClientListener.h>
#include <ClientSession.h>
#include <ClientPool.h>

ClientListener::ClientListener( string address , int port )
    : MRT::Listener( address , port )
{
    Logger::Log( "client listener on %:%" , address , port );
}

ClientListener::~ClientListener()
{
}

Session * ClientListener::CreateSession()
{
    return new ClientSession();
}

void ClientListener::OnSessionOpen( Session * session )
{
    ClientPool::Instance()->Push( (ClientSession*)session );
    Logger::Log( "client %:% connected", session->ip_address() , session->port() );
}

void ClientListener::OnSessionClose( Session * session )
{
    Logger::Log( "client %:% disconnected", session->ip_address() , session->port() );
    ClientSession * client = ( ClientSession* ) session;
    client->CloseFile();
    ClientPool::Instance()->Pop( (ClientSession*)session );
    SAFE_DELETE( session );
}

#include <MRT.h>
#include <NodeListener.h>
#include <ClientListener.h>
#include <MessageHub.h>
#include <ObjectPool.h>
#include <MelotonMaster.h>
#include <Path.h>
#include <HTTPListener.h>
#include <DirectoryMetaTest.hpp>

int main( int argc , char* argv[] )
{ 
    Logger::Sys("meloton master start");

    MRT::Maraton::Instance()->Regist( make_sptr( NodeListener , "0.0.0.0" , MASTER_NODE_PORT ) );
    MRT::Maraton::Instance()->Regist( make_sptr( ClientListener , "0.0.0.0" , MASTER_CLIENT_PORT) );
    MRT::Maraton::Instance()->Regist( make_sptr( HTTPListener , "0.0.0.0" , HTTP_PORT) );

    while ( true )
    {
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}
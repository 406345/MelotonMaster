#include <MRT.h>
#include <NodeListener.h>
#include <ClientListener.h>
#include <MessageHub.h>
#include <ObjectPool.h>
#include <MelotonMaster.h>
#include <Path.h>
#include <DirectoryMetaTest.hpp>

int main( int argc , char* argv[] )
{ 
    Logger::Sys("meloton master start");

    MRT::Maraton::Instance()->Regist( make_sptr( NodeListener ) );
    MRT::Maraton::Instance()->Regist( make_sptr( ClientListener , "0.0.0.0" , 101) );

    while ( true )
    {
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}
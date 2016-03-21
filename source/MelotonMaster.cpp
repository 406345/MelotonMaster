#include <MRT.h>
#include <NodeListener.h>
#include <MessageHub.h>
#include <ObjectPool.h>
#include <MelotonMaster.h>
#include <Path.h>

#include <DirectoryMetaTest.hpp>

int main( int argc , char* argv[] )
{ 

    DirectoryMetaTest test;
    test.StartTest();


    scanf( "" );

    Logger::Sys("meloton master start");

    MRT::Maraton::Instance()->Regist( make_sptr( NodeListener ) );

    while ( true )
    {
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}
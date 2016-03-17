#include <MRT.h>
#include <NodeListener.h>
#include <MessageHub.h>
#include <ObjectPool.h>
#include <MelotonMaster.h>

int main( int argc , char* argv[] )
{
    Logger::Sys("Meloton system start");

    MRT::Maraton::Instance()->Regist( make_sptr( NodeListener ) );

    while ( true )
    {
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}
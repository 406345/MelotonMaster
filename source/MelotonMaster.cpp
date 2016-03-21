#include <MRT.h>
#include <NodeListener.h>
#include <MessageHub.h>
#include <ObjectPool.h>
#include <MelotonMaster.h>
#include <Path.h>

int main( int argc , char* argv[] )
{

    Path p2( "/abc.fastq" );
    Path p4( "/abc.fastq." );
    Path p3( "/abc" );
    Path p( "/abc/eee/" , "123" );
    Path p1( "abc/bccc/" , "123");
     
    auto l = Timer::Date();

    Logger::Sys("meloton master start");

    MRT::Maraton::Instance()->Regist( make_sptr( NodeListener ) );

    while ( true )
    {
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}
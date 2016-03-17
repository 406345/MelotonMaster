#include <NodeListener.h>
#include <NodeSession.h>
#include <NodeSessionPool.h>
#include <MRT.h>
#include <MelotonMaster.h>

NodeListener::NodeListener()
    : MRT::Listener( "0.0.0.0" , 100 )
{
    MRT::SyncWorker::Create(
        1000 ,
        [ ] ( MRT::SyncWorker* worker )
        {
            NodeSessionPool::Instance()->Each( [ ] ( NodeSession* session )
            {
                if( session->AliveTime() > NODE_TIMEOUT )
                {
                    session->close();
                }
            } );

            return false;
        } , nullptr , nullptr );
}

NodeListener::~NodeListener()
{

}

Session * NodeListener::CreateSession()
{
    return new NodeSession();
}

void NodeListener::OnSessionOpen( Session * session )
{
    NodeSessionPool::Instance()->Push( scast<NodeSession*>( session ) );
}

void NodeListener::OnSessionClose( Session * session )
{
    NodeSessionPool::Instance()->Pop( scast<NodeSession*>( session ) );
}

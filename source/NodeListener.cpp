/***********************************************************************************
This file is part of Project for Meloton
For the latest info, see  https://github.com/Yhgenomics/MelotonMaster.git

Copyright 2016 Yhgenomics

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************************/

/***********************************************************************************
* Description   :
* Creator       : Shubo Yang
* Date          :
* Modifed       : When      | Who       | What
***********************************************************************************/

#include <NodeListener.h>
#include <NodeSession.h>
#include <NodeSessionPool.h>
#include <MRT.h>
#include <MelotonMaster.h>

NodeListener::NodeListener( std::string ip , int port )
    : MRT::Listener( ip , port )
{
    Logger::Sys( "node listener on %:%" , this->Address().c_str() , this->Port() );

    MRT::SyncWorker::Create(
        1000 ,
        [ ] ( MRT::SyncWorker* worker )
    {

        NodeSessionPool::Instance()->Each( [ ] ( NodeSession* session )
        {
            if ( session->AliveTime() > NODE_TIMEOUT )
            {
                Logger::Error( "session(%:%) timeout" , session->ip_address() , session->port() );
                session->Close();
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
    auto node = scast<NodeSession*>( session );
    NodeSessionPool::Instance()->Push( node );
    Logger::Log( "node %:% connected" , session->ip_address() , session->port() );
}

void NodeListener::OnSessionClose( Session * session )
{
    auto node = scast<NodeSession*>( session );
    node->RemvoeBlock();
    NodeSessionPool::Instance()->Pop( node );
    Logger::Log( "node %:% disconnected" , session->ip_address() , session->port() );
    SAFE_DELETE( session );
}

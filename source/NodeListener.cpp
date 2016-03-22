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

NodeListener::NodeListener()
    : MRT::Listener( "0.0.0.0" , 100 )
{ 
    Logger::Sys( "node listener IP : %:%" , this->Address().c_str() , this->Port() );

    MRT::SyncWorker::Create(
        1000 ,
        [ ] ( MRT::SyncWorker* worker )
        {
            NodeSessionPool::Instance()->Each( [ ] ( NodeSession* session )
            {
                if( session->AliveTime() > NODE_TIMEOUT )
                {
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
    NodeSessionPool::Instance()->Push( scast<NodeSession*>( session ) );
}

void NodeListener::OnSessionClose( Session * session )
{
    NodeSessionPool::Instance()->Pop( scast<NodeSession*>( session ) );
}
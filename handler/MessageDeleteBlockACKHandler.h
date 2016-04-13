/***********************************************************************************
This file is part of Project for Meloton
For the latest info, see  https://github.com/Yhgenomics/MelotonClient.git
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
* Description   : MessageDeleteBlockACK handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-04-13
* Modifed       : 2016-04-13      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageDeleteBlockACK.pb.h>
#include <NodeSessionPool.h>
#include <ClientPool.h>
#include <FileDictionary.h>
#include <MessageDeleteFileACK.pb.h>

static int MessageDeleteBlockACKHandler( MRT::Session * session , uptr<MessageDeleteBlockACK> message )
{
    auto s    = scast<MelotonSession*>( session );
    auto node = NodeSessionPool::Instance()->FindById( s->Id() );

    if ( node == nullptr )
    {
        return -1;
    }


    auto client = ClientPool::Instance()->FindById( message->clientid() );

    if ( client == nullptr )
    {
        Logger::Error( "can't find client when deleting block %:%" , 
                       session->ip_address() ,
                       message->index() );
        return 0;
    }

    auto file  = FileDictionary::Instance()->FindFile( make_sptr( Path , message->path() ) );
    
    if ( file == nullptr )
    {
        Logger::Error( "can't find % when deleting " , 
                       message->path() );

        uptr<MessageDeleteFileACK> msg = make_uptr( MessageDeleteFileACK );
        msg->set_code( 1 );
        msg->set_message( "can't find file when deleting" );
        msg->set_path( message->path() );
        client->SendMessage( move_ptr( msg ) );
        client->Close();

        return 0;
    }
    
    auto block = file->FindBlock( message->partid() );
    
    if ( block == nullptr )
    {
        Logger::Error( "can't %(Part %) when deleting" , 
                       message->path(),
                       message->partid() );

        uptr<MessageDeleteFileACK> msg = make_uptr( MessageDeleteFileACK );
        msg->set_code( 1 );
        msg->set_message( "can't find part when deleting" );
        msg->set_path( message->path() );
        client->SendMessage( move_ptr( msg ) );
        client->Close();

        return 0;
    }

    block->RemoveNode( node->Id() );

    client->AddBlock( move_ptr( message ) );

    return 0;
}

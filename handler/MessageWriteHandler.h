/***********************************************************************************
This file is part of Project for MaratonServant
For the latest info, see  https://github.com/Yhgenomics/MaratonServant.git
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
* Description   : MessageWrite handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-17
* Modifed       : When      | Who       | What
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageWrite.pb.h>
#include <ClientTokenPool.h>
#include <ClientSession.h>
#include <FileDispatcher.h>
#include <FileDictionary.h>
#include <MessagePrepareWrite.pb.h>
#include <NodeSessionPool.h>
#include <NodeSession.h>
#include <MessageError.pb.h>

static int MessageWriteHandler( MRT::Session * session , uptr<MessageWrite> message )
{
    auto client = scast<ClientSession*>( session );
    auto offset = message->offset();
    auto size   = message->size();
    auto token  = message->token();

    if ( client->State() != ClientState::kIdle )
        return 0;
    
    if ( token.empty() )
    {
        return -1;
    }

    auto t = ClientTokenPool::Instance()->CheckToken( token );

    if ( t == nullptr )
    {
        return -1;
    }


    auto block_num      = FileDispatcher::Instance()->DispatchWrite( t , 
                                                                     offset ,
                                                                     size );

    client->SetState    ( ClientState::kWaitingForBlock );
    client->SetBlockNum ( block_num );

    auto file           = FileDictionary::Instance()->FindFile( make_sptr( Path , t->Path() ) );
    auto blocks         = file->BlockList();
    auto new_block_num  = block_num - blocks.size();
    auto new_part       = blocks.size();

    for ( size_t i = 0; i < blocks.size(); i++ )
    {
        auto block = blocks[i];
        auto node  = block->IdleNode();

        if ( node == nullptr )
        {
            auto reply = make_uptr( MessageError );
            reply->set_code( ERR_NO_NODE );
            reply->set_message( "can't find any node" );
            client->SendMessageW( move_ptr( reply ) );
            return -1;
        }

        uptr<MessagePrepareWrite> msg = make_uptr( MessagePrepareWrite );
        msg->set_isnew( false );
        msg->set_clientid( client->Id() );
        msg->set_fileoffset( block->FileOffset() );
        msg->set_index( node->Index() );
        msg->set_partid( block->PartId() );
        msg->set_path( t->Path() );
        node->Session()->SendMessage( move_ptr( msg ) );
        offset+= block->Size();
    }

    for ( size_t i = 0; i < new_block_num; i++ )
    {
        uptr<MessagePrepareWrite> msg = make_uptr( MessagePrepareWrite );
        msg->set_isnew( true );
        msg->set_clientid( client->Id() );
        msg->set_fileoffset( offset );
        msg->set_index( 0 );
        msg->set_partid( new_part + i );
        msg->set_path( t->Path() );
        offset += BLOCK_SIZE;

        NodeSession * node = NodeSessionPool::Instance()->AvailableNode();
        if ( node != nullptr )
        {
            node->SendMessage( move_ptr( msg ) );
        }
    }

    return 0;
}

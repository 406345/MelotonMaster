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
* Description   : MessageRead handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-17
* Modifed       : When      | Who       | What
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageRead.pb.h>
#include <ClientTokenPool.h>
#include <FileDictionary.h>
#include <ClientSession.h>
#include <MessagePrepareRead.pb.h>

static int MessageReadHandler( MRT::Session * session , uptr<MessageRead> message )
{
    auto client    = scast<ClientSession*>( session );
    auto token_str = message->token();
    auto size      = message->size();
    auto offset    = message->offset();

    auto token     = ClientTokenPool::Instance()->CheckToken( token_str );

    if ( token == nullptr )
    {
        return -1;
    }

    auto file = FileDictionary::Instance()->FindFile( make_sptr( Path , token->Path() ) );

    if ( file == nullptr )
    { 
        auto err_msg = make_uptr( MessageError );
        err_msg->set_code( ERR_FILE_NOT_EXIST  );
        err_msg->set_message( "file do not exist" );
        client->SendMessageW( move_ptr( err_msg ) );
        return -1;
    }

    auto block_list = file->BlockRange( offset , size );

    if ( block_list.size() == 0 )
    {
        auto err_msg = make_uptr( MessageError );
        err_msg->set_code( ERR_NO_BLOCK  );
        err_msg->set_message( "block do not exist" );
        client->SendMessageW( move_ptr( err_msg ) );
        return -1;
    }

    client->SetBlockNum( block_list.size() );
    client->SetState( ClientState::kWaitingForBlock );

    for ( size_t i = 0; i < block_list.size(); i++ )
    {
        auto block = block_list[i];
        auto node  = block->IdleNode();

        if ( node == nullptr )
        {
            auto reply = make_uptr( MessageError );
            reply->set_code( ERR_NO_NODE );
            reply->set_message( "can't find any node" );
            client->SendMessageW( move_ptr( reply ) );
            return -1;
        }

        uptr<MessagePrepareRead> msg = make_uptr( MessagePrepareRead );
        msg->set_clientid( client->Id() );
        msg->set_index( node->Index() );
        node->Session()->SendMessage( move_ptr( msg ) );
        offset+= block->Size();
    }


    return 0;
}

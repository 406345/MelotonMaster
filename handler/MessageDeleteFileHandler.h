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
* Description   : MessageDeleteFile handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-04-13
* Modifed       : 2016-04-13      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageDeleteFile.pb.h>
#include <ClientSession.h>
#include <ClientPool.h>
#include <ClientTokenPool.h>
#include <MessageError.pb.h>
#include <ErrorCode.h>
#include <FileDictionary.h>
#include <MessageDeleteBlock.pb.h>

static int MessageDeleteFileHandler( MRT::Session * session , uptr<MessageDeleteFile> message )
{
    auto s     = scast<MelotonSession*>( session );
    auto token = ClientTokenPool::Instance()->CheckToken( message->token() );

    if ( token == nullptr )
    {
        uptr<MessageError> err = make_uptr( MessageError );
        err->set_code( ERR_TOKEN_NOT_EXIST );
        err->set_message( "token not exist" );
        s->SendMessage( move_ptr( err ) );
        return -1;
    }

    auto client = ClientPool::Instance()->FindById( token->ClientId() );

    if ( client == nullptr )
    {
        uptr<MessageError> err = make_uptr( MessageError );
        err->set_code( ERR_INVAILED_CLIENT );
        err->set_message( "unknown client" );
        s->SendMessage( move_ptr( err ) );
        return -1;
    }

    client->SetState( ClientState::kWaitingForDelete );

    auto file = FileDictionary::Instance()->FindFile( make_sptr( Path , message->path() ) );

    if ( file->IsOpened() )
    {
        uptr<MessageError> err = make_uptr( MessageError );
        err->set_code( ERR_FILE_ALREADY_OPENTED );
        err->set_message( "file is already opened" );
        s->SendMessage( move_ptr( err ) );
        return -1;
    }

    auto   blocks       = file->BlockList();
    size_t block_num    = 0;

    for ( auto & block : blocks )
    {
        auto nodes = block->NodeList();

        for ( auto & n : nodes )
        {
            if ( n == nullptr ||
                 n->Session() == nullptr )
            {
                continue;
            }

            block_num++;
            uptr<MessageDeleteBlock> msg    = make_uptr( MessageDeleteBlock );
            msg->set_clientid( client->Id() );
            msg->set_index( n->Index() );
            n->Session()->SendMessage( move_ptr( msg ) );
        }
    }

    client->SetBlockNum( block_num );

    return 0;
}

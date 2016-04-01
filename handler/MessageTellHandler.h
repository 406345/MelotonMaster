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
* Description   : MessageTell handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-04-01
* Modifed       : 2016-04-01      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageTell.pb.h>
#include <ClientTokenPool.h>
#include <FileDictionary.h>
#include <ClientSession.h>
#include <ErrorCode.h>
#include <MessageError.pb.h>
#include <MessageTellACK.pb.h>

static int MessageTellHandler( MRT::Session * session , uptr<MessageTell> message )
{
    auto client =  scast<ClientSession*>( session );
    auto token  = message->token();
    auto path   = message->path();

    auto t = ClientTokenPool::Instance()->CheckToken( token );

    if ( t == nullptr )
    {
        return -1;
    }

    auto file = FileDictionary::Instance()->FindFile( make_sptr( Path , path ) );

    if ( file == nullptr )
    { 
        auto err_msg = make_uptr( MessageError );
        err_msg->set_code( ERR_FILE_NOT_EXIST  );
        err_msg->set_message( "file do not exist" );
        client->SendMessageW( move_ptr( err_msg ) );
        return -1;
    }

    auto result = make_uptr( MessageTellACK );
    result->set_path( path );
    result->set_size( file->Size() );
    result->set_token( token );
    client->SendMessage( move_ptr( result ) );

    return 0;
}

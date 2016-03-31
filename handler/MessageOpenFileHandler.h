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
* Description   : MessageOpenFile handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-17
* Modifed       : 2016-03-22  | Shubo Yang  | Impl 
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageError.pb.h>
#include <MessageOpenFile.pb.h>
#include <FileDictionary.h>
#include <ErrorCode.h>
#include <MessageOpenACK.pb.h>
#include <ClientTokenPool.h>
#include <MessageOpenACK.pb.h>
#include <ClientSession.h>

static int MessageOpenFileHandler( MRT::Session * session , uptr<MessageOpenFile> message )
{
    auto path  = make_sptr( Path , message->path() );
    auto file  = FileDictionary::Instance()->FindFile( path );
    auto client  = scast<ClientSession*>( session );
    auto reply = make_uptr( MessageOpenACK );

    if ( file == nullptr )
    {
        file = FileDictionary::Instance()->CreateFile( path );
    }

    client->OpenFile( file );

    if ( file != nullptr && file->IsOpened() )
    {
        reply->set_token( "" );
        reply->set_code( ERR_FILE_ALREADY_OPENTED );
        reply->set_message( "file already opened" );
        client->SendMessage( move_ptr( reply ) );
        return -1;
    } 

    auto token = ClientTokenPool::Instance()->CreateToken( client->Id() );
    token->Path( message->path() );
    client->OpenToken( token );

    if ( file->Open( token->Token() ) )
    {
        reply->set_code( 0 );
        reply->set_message( "" );
        reply->set_token( token->Token() );
        client->SendMessage( move_ptr( reply ) );
    }
    else
    {
        uptr<MessageOpenACK> error = make_uptr( MessageOpenACK );
        reply->set_token( "" );
        reply->set_code( ERR_FILE_OPEN_FAILED );
        reply->set_message( "open file failed" );
        client->SendMessage( move_ptr( error ) );
        return -1;
    }

    return 0;
}

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

static int MessageOpenFileHandler( MRT::Session * session , uptr<MessageOpenFile> message )
{
    auto path  = make_sptr( Path , message->path() );
    auto file  = FileDictionary::Instance()->FindFile( path );
    auto node  = scast<NodeSession*>( session );
    auto reply = make_uptr( MessageOpenACK );

    if ( file == nullptr )
    {
        uptr<MessageOpenACK> error = make_uptr( MessageOpenACK );
        reply->set_code( ERR_FILE_NOT_EXIST );
        reply->set_message( "files not exist" );
        node->SendMessage( move_ptr( error ) );
        return -1;
    }

    if ( file->IsOpened() )
    {
        uptr<MessageOpenACK> error = make_uptr( MessageOpenACK );
        reply->set_code( ERR_FILE_ALREADY_OPENTED );
        reply->set_message( "files already opened" );
        node->SendMessage( move_ptr( error ) );
        return -1;
    }

    auto token = ClientTokenPool::Instance()->CreateToken( node->Id() );
    
    if ( file->Open( token->Token() ) )
    {
        reply->set_code( 0 );
        reply->set_message( "" );
        reply->set_token( token->Token() );
        reply->set_blockcount( file->BlockList().size() );
        node->SendMessageW( move_ptr( reply ) );
        token->Path( message->path() );
    }
    else
    {
        uptr<MessageOpenACK> error = make_uptr( MessageOpenACK );
        reply->set_code( ERR_FILE_OPEN_FAILED );
        reply->set_message( "files open failed" );
        node->SendMessage( move_ptr( error ) );
        return -1;
    }

    return 0;
}

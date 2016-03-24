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

static int MessageWriteHandler( MRT::Session * session , uptr<MessageWrite> message )
{
    auto client = scast<ClientSession*>( session );
    auto offset = message->offset();
    auto size   = message->size();
    auto token  = message->token();
    
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

    auto file           = FileDictionary::Instance()->FindFile( make_sptr( Path , t->Path() ) );
    auto blocks         = file->BlockList();
    auto new_block_num  =  block_num - blocks.size();

    for ( size_t i = 0; i < blocks.size(); i++ )
    {
        uptr<MessagePrepareWrite> msg = make_uptr( MessagePrepareWrite );
        auto block = blocks[i];
        msg->set_clientid( client->Id() );
        msg->set_fileoffset( block->FileOffset() );
        msg->set_index( block->IdleNode()->Index() );
        msg->set_index( block->PartId() );
        block->IdleNode()->Session()->SendMessage( move_ptr( msg ) );
    }

    for ( size_t i = 0; i < new_block_num; i++ )
    {

    }

    return 0;
}

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
* Description   : MessageNewBlock handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-04-07
* Modifed       : 2016-04-07      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageNewBlock.pb.h>
#include <FileDictionary.h>
#include <NodeSessionPool.h>
#include <MessageDuplicateBlock.pb.h>

static int MessageNewBlockHandler( MRT::Session * session , uptr<MessageNewBlock> message )
{
    auto node = scast<NodeSession*>( session );
    auto file = FileDictionary::Instance()->FindFile( make_sptr( Path , message->path() ) );

    if ( file == nullptr )
    {
        return 0;
    }

    auto block = file->FindBlock( message->partid() );

    if ( block == nullptr )
    {
        return 0;
    }

    if ( block->NodeCount() == 0 )
    {
        Logger::Error( "MessageNewBlockHandler : node is zero" );
        return 0;
    }

    auto duplicate_delta = DUPLICATE_COUNT - block->NodeCount();

    if ( duplicate_delta == 0 )
    {
        auto nl = block->NodeList();
        
        for ( auto & n : nl )
        {
            auto duplicate_msg = make_uptr( MessageDuplicateBlock );
            duplicate_msg->set_address    ( n->Session()->ip_address() );
            duplicate_msg->set_port       ( NODE_CLIENT_PORT );
            duplicate_msg->set_index      ( message->index() );
            duplicate_msg->set_token      ( message->token() );
            duplicate_msg->set_path       ( message->path() );
            duplicate_msg->set_partid     ( message->partid() );
            duplicate_msg->set_fileoffset ( message->fileoffset() );
            n->Session()->SendMessage( move_ptr( duplicate_msg ) );
        }
    }
    else
    {
        NodeSessionPool::Instance()->Sort( [ ] ( NodeSession* left , NodeSession * right )
        {
            return left->BlockCount() > right->BlockCount();
        } );

        auto p_msg = message.get();

        NodeSessionPool::Instance()->Each( [&duplicate_delta ,
                                           node ,
                                           p_msg] ( NodeSession* obj )
        {
            if ( obj->Id() != node->Id() )
            {
                if ( duplicate_delta > 0 )
                {
                    auto duplicate_msg = make_uptr( MessageDuplicateBlock );
                    duplicate_msg->set_address    ( node->ip_address() );
                    duplicate_msg->set_port       ( NODE_CLIENT_PORT );
                    duplicate_msg->set_index      ( p_msg->index() );
                    duplicate_msg->set_token      ( p_msg->token() );
                    duplicate_msg->set_path       ( p_msg->path() );
                    duplicate_msg->set_partid     ( p_msg->partid() );
                    duplicate_msg->set_fileoffset ( p_msg->fileoffset() );
                    obj->SendMessage( move_ptr( duplicate_msg ) );
                }
                --duplicate_delta;
            }
        } );
    }

    return 0;
}

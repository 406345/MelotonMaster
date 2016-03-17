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
* Description   : MessageAlive handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-17
* Modifed       : When      | Who       | What
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageAlive.pb.h>
#include <NodeSession.h>

static int MessageAliveHandler( MRT::Session * session , uptr<MessageAlive> message )
{
    NodeSession* node = scast<NodeSession*>( session );

    if ( node == nullptr )
        return -1;

    node->AliveTime  ( Timer::Tick() );
    node->CPU        ( message->cpu() );
    node->Memory     ( message->memory() );
    node->BlockCount ( message->blockcount() );

    return 0;
}

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
* Description   : MessageBlockMeta handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-17
* Modifed       : When      | Who       | What
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageBlockMeta.pb.h>
#include <FileDictionary.h>

static int MessageBlockMetaHandler( MRT::Session * session , uptr<MessageBlockMeta> message )
{
    FileDictionary::Instance()->AddBlockMeta( 
            scast<NodeSession*>( session ) , 
            *message.get() );

    return 0;
}

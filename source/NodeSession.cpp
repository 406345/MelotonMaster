/***********************************************************************************
This file is part of Project for Meloton
For the latest info, see  https://github.com/Yhgenomics/MelotonMaster.git

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
* Description   :
* Creator       : Shubo Yang
* Date          :
* Modifed       : When      | Who       | What
***********************************************************************************/

#include <NodeSession.h>
#include <FileMeta.h>

NodeSession::NodeSession()
{
    this->UpdateAliveTime();
}

NodeSession::~NodeSession()
{
}

void NodeSession::UpdateAliveTime()
{
    this->alive_time_ = Timer::Tick() / 1000;
}

size_t NodeSession::AliveTime()
{
    return ( Timer::Tick() / 1000 - this->alive_time_ );
}

void NodeSession::AddBlock( sptr<BlockMeta> blockMeta )
{
    for ( auto & b : this->block_list_ )
    {
        if ( b->Parent() == blockMeta->Parent() &&
             b->PartId() == blockMeta->PartId() )
        {
            return;
        }
    }

    this->block_list_.push_back( blockMeta );
}

void NodeSession::RemvoeBlock()
{
    for ( auto & block : this->block_list_ )
    {
        block->RemoveNode( this->Id() ); 
    }
}

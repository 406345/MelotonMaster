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

#include <NodeSessionPool.h>

NodeSession * NodeSessionPool::FindById( size_t id )
{
    return this->Find( [ &id ] ( NodeSession* object )
    {
        if ( object->Id() == id )
            return true;

        return false;
    } );
}

NodeSession * NodeSessionPool::AvailableNode()
{
    this->Sort( [ ] ( NodeSession* left , NodeSession * right ) { 
        return left->BlockCount() > right->BlockCount();
    } );

    return this->First();
}

NodeSession * NodeSessionPool::AvailableDuplicateNode( NodeSession * session )
{
    this->Sort( [ ] ( NodeSession* left , NodeSession * right ) { 
        return left->BlockCount() > right->BlockCount();
    } );

    return this->Find( [ session ] ( NodeSession* node ) { 
        return node->Id() == session->Id();
    } );
}

void NodeSessionPool::SortDesc()
{
    this->Sort( [ ] ( NodeSession* left , NodeSession * right ) { 
        return left->BlockCount() > right->BlockCount();
    } );

}

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
* Date          : 2016-03-21
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef BLOCK_META_H_
#define BLOCK_META_H_

#include <vector>
#include <MRT.h>
#include <NodeMeta.h>

using std::vector;

class FileMeta;

class BlockMeta
{
public: 

    size_t          PartId      ();
    void            PartId      ( size_t value );

    size_t          Size         ();
    void            Size         ( size_t value );

    size_t          BlockSize    ();
    void            BlockSize    ( size_t value );

    size_t          FileOffset   ();
    void            FileOffset   ( size_t value );

    void            AddNode      ( sptr<NodeMeta> nodemeta );
    void            RemoveNode   ( size_t session_id );
    size_t          NodeCount    ();

    sptr<NodeMeta>  FindNode     ( size_t session_id);
    sptr<NodeMeta>  IdleNode     ();

    sptr<FileMeta>  Parent       ();
    void            Parent       ( sptr<FileMeta> parent );

private:

    size_t part_id_     = 0;
    size_t size_        = 0;
    size_t file_offset_ = 0;
    size_t block_size_  = 0;

    vector<sptr<NodeMeta>> node_list_;
    sptr<FileMeta>         parent_;
};

#endif // !BLOCK_META_H_ 
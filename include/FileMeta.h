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

#ifndef FILE_META_H_
#define FILE_META_H_

#include <string>
#include <vector>
#include <MRT.h>
#include <Path.h>
#include <BlockMeta.h>

using std::string;
using std::vector;

class FileMeta
{
public:

    FileMeta  () { };
    ~FileMeta () { };
                            
    bool IsOpened()             { return this->is_open_ == true;    };
    size_t Size()               { return size_;                     };
    string Name()               { return name_;                     };
    string OwnerToken()         { return this->owner_token_;        };
    sptr<Path> FilePath()       { return this->path_;               };

    void FilePath( sptr<Path> value );
    
    bool Open( string token );
    bool Close( string token );
    bool AddBlock( sptr<BlockMeta> block );
    bool RemoveBlock( sptr<BlockMeta> block );
    
    vector<sptr<BlockMeta>> BlockRange( size_t offset , size_t size );
    vector<sptr<BlockMeta>> BlockList();

private:

    string                    name_          = "";
    size_t                    size_          = 0;
    sptr<Path>                path_          = nullptr;
    bool                      is_open_       = false;
    string                    owner_token_   = "";
    vector<sptr<BlockMeta>>   block_list_;
};

#endif // !FILE_META_H_ 
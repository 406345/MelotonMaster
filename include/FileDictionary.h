/***********************************************************************************
This file is part of Project for MaratonFramework
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

#ifndef FILE_DIECTIONARY_H_
#define FILE_DIECTIONARY_H_

#include <MelotonMaster.h>
#include <DirectorMeta.h>
#include <MessageBlockMeta.pb.h>
#include <NodeSession.h>
#include <FileMeta.h>
#include <Path.h>

class FileDictionary
{
public:

    SINGLETON_DEF( FileDictionary );

    void           AddBlockMeta ( NodeSession* session , 
                                  const MessageBlockMeta & message );

    sptr<FileMeta> FindFile     ( sptr<Path> path );
    sptr<FileMeta> CreateFile   ( sptr<Path> path );

private:

    FileDictionary ();
    ~FileDictionary();

    sptr<DirectorMeta> director_ = nullptr;
};

#endif // !FILE_DIECTIONARY_H_
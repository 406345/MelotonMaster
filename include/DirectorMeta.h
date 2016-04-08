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

#ifndef DIRECTOR_META_H_
#define DIRECTOR_META_H_

#include <vector>
#include <MRT.h>
#include <Path.h>
#include <FileMeta.h>

using std::vector;

class DirectorMeta : 
    public std::enable_shared_from_this<DirectorMeta>
{
public:

    // Root dir
    DirectorMeta ();

    // Make dirs with path
    ~DirectorMeta();

    bool               operator ==  ( string path );
    bool               operator ==  ( sptr<DirectorMeta> meta );
    bool               operator ==  ( sptr<Path> path );

    string             Name         () { return this->path_; };

    sptr<DirectorMeta> FindDirector ( sptr<Path> path );
    sptr<FileMeta>     FindFile     ( sptr<Path> path );
    bool               AddFile      ( sptr<FileMeta> file );
    sptr<DirectorMeta> MakeDirector ( sptr<Path> path );
    bool               ExistFile    ( sptr<Path> path );

    vector<sptr<DirectorMeta>> ChildrenDir( );
    vector<sptr<FileMeta>>     Files( );

private:

    string                     path_                = "/";
    string                     full_path_           = "/";
    vector<sptr<DirectorMeta>> children_dir_list_;
    vector<sptr<FileMeta>>     file_list_;

    sptr<DirectorMeta>         find_dir( string name );

};

#endif // !DIRECTOR_META_H_ 
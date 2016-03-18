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

#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class Path
{
public:

    Path( string path );
    Path( string path , string filename );

    string          FileNameWithoutExtention () { return this->filename_without_extention_; };
    string          FileName                 () { return this->filename_; };
    string          FileExtention            () { return this->filename_extention_; };
    vector<string>  PathList                 () { return vector<string>( this->path_list_ ); };

private:

    string          original_path_              = "";
    string          original_filename_          = "";
    string          filename_                   = "";
    string          filename_without_extention_ = "";
    string          filename_extention_         = "";
    vector<string>  path_list_;

    void ParsePath();
    void ParseFilename();
};

#endif // !PATH_H_ 
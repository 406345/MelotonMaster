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

#ifndef FILE_DISPACHTER_H_
#define FILE_DISPACHTER_H_

#include <vector>
#include <MRT.h>
#include <MelotonMaster.h>
#include <DirectorMeta.h>
#include <ClientTokenPool.h>

using std::vector;

class FileDispatcher
{
public:
    
    MAKE_SINGLETON ( FileDispatcher );

    size_t DispatchWrite( sptr<ClientToken> token ,
                          size_t offset ,
                          size_t size );

private:

    FileDispatcher ();
    ~FileDispatcher();
     
};

#endif // !FILE_DISPACHTER_H_ 
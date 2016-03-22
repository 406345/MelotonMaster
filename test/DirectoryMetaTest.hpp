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

#ifndef DIRECTORY_META_TEST_H_
#define DIRECTORY_META_TEST_H_

#include <TestClass.hpp>
#include <DirectorMeta.h>
#include <Path.h>
#include <FileMeta.h>

class DirectoryMetaTest :
    public TestClass
{
public:

    void StartTest() override
    {
        Test1();
        Test2();
    }

    void Test1()
    {
        auto meta = make_sptr( DirectorMeta );
        auto pf   = meta->MakeDirector( make_sptr( Path , "/root/d1/d2/d3/d4/" ) );
        pf->AddFile( make_sptr( FileMeta ) );

        auto t1 = meta->FindDirector( make_sptr( Path , "/root/d1/" ) );
        this->Asset( "Test 1 Case 1" , t1->Name() == "d1" );
        t1->MakeDirector( make_sptr( Path , "d11/d22/" ) );

        auto t2 = meta->FindDirector( make_sptr( Path , "/d1/" ) );
        this->Asset( "Test 1 Case 2" , t2 == nullptr );

        auto t3 = meta->FindDirector( make_sptr( Path , "/d2/" ) );
        this->Asset( "Test 1 Case 3" , t3 == nullptr );

        auto t4 = meta->FindDirector( make_sptr( Path , "/root/d1/d2/d3/d4/" ) );
        this->Asset( "Test 1 Case 4" , t4->Name() == "d4" );

        auto t5 = meta->FindDirector( make_sptr( Path , "/root/d1/d4/" ) );
        this->Asset( "Test 1 Case 5" , t5 == nullptr );

        auto t6 = meta->FindDirector( make_sptr( Path , "/root/d1/d11/" ) );
        this->Asset( "Test 1 Case 6" , t6->Name() == "d11" );

        auto t7 = meta->FindFile( make_sptr( Path , "/root/d1/d2/d3/d4/file1" ) );
        this->Asset( "Test 1 Case 7" , t7 != nullptr && t7->Name() == "file1" );

        auto t8 = meta->FindDirector( make_sptr( Path , "/root/d1/d2/" ) );
        this->Asset( "Test 1 Case 8" , t8 != nullptr && t8->Name() == "d2" );
        t8->AddFile( make_sptr( FileMeta ) );

        auto t9 = meta->FindFile( make_sptr( Path , "/root/d1/d2/file2" ) );
        this->Asset( "Test 1 Case 9" , t9 != nullptr && t9->Name() == "file2" );

    }

    void Test2()
    {

    }
};

#endif // !DIRECTORY_META_TEST_H_ 
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

#ifndef NODE_SESSION_H_
#define NODE_SESSION_H_

#include <MRT.h>
#include <MelotonSession.h>

class NodeSession
    : public MelotonSession
{
public:

    NodeSession  ()
    {
        this->UpdateAliveTime();
    };

    ~NodeSession ()
    {

    };

    void UpdateAliveTime();

    size_t AliveTime    () { return ( Timer::Tick() - this->alive_time_ ); }
    size_t CPU          () { return this->cpu_; }
    size_t Memory       () { return this->memory_; }
    size_t BlockCount   () { return this->block_count_; }

    void   AliveTime    ( size_t value ) { this->alive_time_  = value; }
    void   CPU          ( size_t value ) { this->cpu_         = value; }
    void   Memory       ( size_t value ) { this->memory_      = value; }
    void   BlockCount   ( size_t value ) { this->block_count_ = value; }

private:

    size_t alive_time_  = 0;
    size_t cpu_         = 0;
    size_t memory_      = 0;
    size_t block_count_ = 0;
};

#endif // !NODE_SESSION_H_ 
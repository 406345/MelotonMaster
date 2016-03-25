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

#ifndef CLIENT_SESSION_H_
#define CLIENT_SESSION_H_

#include <vector>
#include <MelotonSession.h>
#include <MessagePrepareWriteACK.pb.h>

using std::vector;

class ClientSession :
    public MelotonSession
{
public:

    void        SetState    ( ClientState state );
    void        SetBlockNum ( size_t num );
    void        AddBlock    ( uptr<MessagePrepareWriteACK> ack );

    ClientState State       ()                   { return this->state_; };

private:

    ClientState state_           = ClientState::kIdle;
    size_t      block_total_num_ = 0;

    vector<uptr<MessagePrepareWriteACK>> block_list_;
};

#endif // !CLIENT_SESSION_H_ 
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
#include <FileMeta.h>
#include <ClientTokenPool.h>
#include <MessageSyncBlock.pb.h>
#include <MessagePrepareReadACK.pb.h>

using std::vector;

class ClientSession :
    public MelotonSession
{
public:

    void        OpenFile     ( sptr<FileMeta> file );
    void        CloseFile    ();
    void        SetState     ( ClientState state );
    void        SetBlockNum  ( size_t num );
    void        AddBlock     ( uptr<MessagePrepareReadACK> ack );
    void        AddBlock     ( uptr<MessagePrepareWriteACK> ack );

    void              OpenToken( sptr<ClientToken> token ) { this->open_token_ = token; }
    sptr<ClientToken> OpenToken() { return this->open_token_; }

    ClientState State        (){ return this->state_; };

protected:

    void OnClose()  override;

private:

    ClientState         state_           = ClientState::kIdle;
    size_t              block_total_num_ = 0;
    sptr<FileMeta>      opened_file_     = nullptr;
    sptr<ClientToken>   open_token_      = nullptr;

    vector<uptr<MessagePrepareWriteACK>> write_block_list_;
    vector<uptr<MessagePrepareReadACK>> read_block_list_;
};

#endif // !CLIENT_SESSION_H_ 
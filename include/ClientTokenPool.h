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

#ifndef CLIENT_TOKEN_POOL_H_
#define CLIENT_TOKEN_POOL_H_

#include <string>

#include <MRT.h>
#include <ObjectPool.h>
#include <MelotonMaster.h>

using std::string;

class ClientToken
{
public:

    ClientToken( string path , string token , size_t clientId )
    {
        this->token_ = token;
        this->client_id_ = clientId;
    }

    string Token()                  { return this->token_; };
    size_t ClientId()               { return this->client_id_; }
    string Path()                   { return this->path_; }

    void Token( string value )      { this->token_ = value; };
    void ClientId( size_t value )   { this->client_id_ = value; };
    void Path( string value )       { this->path_ = value; }


private:

    string token_;
    size_t client_id_;
    string path_;
};

class ClientTokenPool :
    public ObjectPool<sptr<ClientToken>>
{
public:

    MAKE_SINGLETON( ClientTokenPool );

    sptr<ClientToken>  CreateToken( size_t clientId );
    bool               RemoveToken( string token );
    sptr<ClientToken>  CheckToken ( string token );
    
private:

    ClientTokenPool () { };
    ~ClientTokenPool() { };

};

#endif // !CLIENT_TOKEN_POOL_H_ 
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

#ifndef HTTP_ROUTER_H_
#define HTTP_ROUTER_H_

#include <map>
#include <functional>
#include <string>
#include <MRT.h>
#include <HTTPSession.h>

using namespace std;
using namespace MRT;

class HTTPRouter
{
public:

    HTTPRouter  ( );
    ~HTTPRouter ( );

    void Route  ( HTTPSession *session ,
                  sptr<HTTPRequest> request ,
                  sptr<HTTPResponse> response);

private:

    typedef function<void( HTTPSession *session , 
                           sptr<HTTPRequest> request , 
                           sptr<HTTPResponse> )> router_handler_t;
    std::map<string , router_handler_t> router_;

    void Register( string url , router_handler_t call );
};

#endif // HTTP_ROUTER_H_
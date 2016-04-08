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

#ifndef HTTP_LISTENER_H_
#define HTTP_LISTENER_H_

#include <string>
#include <MRT.h>
#include <HTTPSession.h>
#include <MelotonMaster.h>

using std::string;
using MRT::Listener;

class HTTPListener :
    public Listener
{
public:
    HTTPListener( string address , int port )
        : Listener( address , port )
    {
        Logger::Log( "http listener on %:%" , address , port );
    };

    ~HTTPListener()
    {
        
    };
protected:

    virtual Session * CreateSession    () override;

    // Callback when a session is created
    virtual void      OnSessionOpen   ( Session * session ) override;

    // Callback after a session is closed
    virtual void      OnSessionClose  ( Session * session ) override;
};

#endif // !HTTP_LISTENER_H_ 
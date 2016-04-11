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

#ifndef HTTP_ROUTER_HANDLER_H_
#define HTTP_ROUTER_HANDLER_H_

#include <string>
#include <MRT.h>
#include <HTTPSession.h>
#include <Json.hpp>
#include <NodeSessionPool.h>
#include <FileDictionary.h>
#include <Path.h>

using namespace MRT;
using namespace nlohmann;
using namespace std;

#define HTTPMETHOD( __method__ ) HTTPHandler##__method__( HTTPSession* session , \
                                             sptr<HTTPRequest> request , \
                                             sptr<HTTPResponse> response )

static void HTTPMETHOD( Node )
{
    json obj;

    NodeSessionPool::Instance( )->Each( [&obj] ( NodeSession* node )
    {
        json jnode;
        jnode["cpu"]        = node->CPU( );
        jnode["memory"]     = node->Memory( );
        jnode["alive"]      = node->AliveTime( );
        jnode["blockcount"] = node->BlockCount( );
        jnode["address"]    = node->ip_address( );
        obj.push_back( jnode );
    } );

    auto result_str = obj.dump();
    response->Content( make_uptr( Buffer , result_str.c_str() , result_str.size() ) );
};

static void HTTPMETHOD( File )
{
    json result;
    json input;

    try
    {
        auto   url  = request->Uri();
        string filepath = url->Parameter( "path" );
        auto   file     = FileDictionary::Instance()->FindFile( make_sptr( Path ,
                                                                filepath ) );

        if ( file == nullptr )
            return;

        result["path"] = file->FilePath()->ToFullPath();
        result["size"] = file->Size();

        for ( auto & block : file->BlockList() )
        {
            json b;
            b["partid"]     = block->PartId();
            b["size"]       = block->Size();
            b["nodecount"]  = block->NodeCount();
            b["node"]       = nlohmann::json::array();

            for ( auto & node : block->NodeList() )
            {
                json nd;
                nd["address"] = node->Session()->ip_address();
                b["node"].push_back( nd );
            }

            result["block"].push_back( b );
        }

    }
    catch ( exception ee )
    {
        response->Content( make_uptr( Buffer , "" ) );
        return;
    }
    
    auto result_str = result.dump();
    response->Content( make_uptr( Buffer , result_str.c_str() , result_str.size() ) );
};

static void HTTPMETHOD( Dir )
{
    json result;
    json input;

    try
    {

        auto   url  = request->Uri();
        string path = url->Parameter("path");
        auto   dir  = FileDictionary::Instance()->FindDir( path );

        if ( dir != nullptr )
        {
            result["dir"] = nlohmann::json::array();
            for ( auto & cd : dir->ChildrenDir() )
            {
                json cdir;
                cdir["path"] = cd->Name();
                result["dir"].push_back( cdir );
            }
            result["dircount"] = dir->ChildrenDir().size();

            result["file"] = nlohmann::json::array();
            for ( auto & file : dir->Files() )
            {
                json cfile;
                cfile["path"]       = file->FilePath()->ToFullPath();
                cfile["size"]       = file->Size();
                cfile["blockcount"] = file->BlockList().size();
                result["file"].push_back( cfile );
            }
            result["filecount"] = dir->Files().size();
        }
    }
    catch ( exception ee )
    {
        response->Content( make_uptr( Buffer , "" ) );
        return;
    }
    
    auto result_str = result.dump();
    response->Content( make_uptr( Buffer , result_str.c_str() , result_str.size() ) );
};

#endif // !HTTP_ROUTER_HANDLER_H_
/***********************************************************************************

This file is part of Project for MaratonFramework
For the latest info, see  https://github.com/Yhgenomics/MaratonFramework.git

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

/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-11
* Description:
* * * * * * * * * * * * * * * */

#ifndef MELOTON_MASTER_H_
#define MELOTON_MASTER_H_ 

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
  Const Section
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
static const long long NODE_TIMEOUT         = 5000;
static const long long BLOCK_SIZE           = 1024 * 1024 * 16;
static const long long DUPLICATE_COUNT      = 3;
static const int       DUPLICATE_PORT       = 99;

static const int    MASTER_NODE_PORT     = 110;
static const int    MASTER_CLIENT_PORT   = 111;
static const int    NODE_CLIENT_PORT     = 112;
static const int    HTTP_PORT            = 80;

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
  Macro Function Section
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define SINGLETON_DEF( __type__ ) static __type__ * Instance() \
{ \
    static __type__ inst_; \
    return &inst_; \
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
  Enum Section
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum MelotonSessionParseState
{
    kHead = 1,
    kLength,
    kBody
};

enum ClientState
{
    kIdle = 1 ,
    kWaitingForBlock = 2,
    kTransfer
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
  Debug Section
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifdef _DEBUG

#define DEBUG_LOG(FMT,... ) Logger::Log( FMT,__VA_ARGS__)

#endif // DEBUG

#endif // !MELOTON_MASTER_H_






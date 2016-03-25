#include <ClientPool.h>

ClientSession * ClientPool::FindById( size_t id )
{
    return this->Find( [&id] ( ClientSession* obj ) { 
        return obj->Id() == id;
    } );
}

ClientPool::ClientPool()
{
}

ClientPool::~ClientPool()
{
}

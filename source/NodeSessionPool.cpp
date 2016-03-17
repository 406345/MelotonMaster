#include <NodeSessionPool.h>

NodeSession * NodeSessionPool::FindById( size_t id )
{
    return this->Find( [ &id ] ( NodeSession* object )
    {
        if ( object->Id() == id )
            return true;

        return false;
    } );
}

#include <NodeMeta.h>

NodeMeta::NodeMeta( size_t index , NodeSession * session )
{
    this->index_ = index;
    this->node_ = session;
}

NodeMeta::~NodeMeta()
{
}

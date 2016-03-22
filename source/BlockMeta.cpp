#include "BlockMeta.h"

size_t BlockMeta::BlockId()
{
    return this->block_id_;
}

void BlockMeta::BlockId( size_t value )
{
    this->block_id_ = value;
}

size_t BlockMeta::Size()
{
    return this->size_;
}

void BlockMeta::Size( size_t value )
{
    this->size_ = value;
}

size_t BlockMeta::BlockSize()
{
    return this->block_size_;
}

void BlockMeta::BlockSize( size_t value )
{
    this->block_size_ = value;
}

size_t BlockMeta::FileOffset()
{
    return this->file_offset_;
}

void BlockMeta::FileOffset( size_t value )
{
    this->file_offset_ = value;
}

void BlockMeta::AddNode( sptr<NodeMeta> nodemeta )
{
    this->node_list_.push_back( nodemeta );
}

sptr<NodeMeta> BlockMeta::FindNode( size_t sessesion_id )
{
    for ( auto & n : this->node_list_ )
    {
        if ( n->Session()->Id() == sessesion_id )
        {
            return n;
        }
    }

    return nullptr;
}

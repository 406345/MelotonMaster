#include "BlockMeta.h"
#include <NodeSession.h>
#include <FileMeta.h>

size_t BlockMeta::PartId()
{
    return this->part_id_;
}

void BlockMeta::PartId( size_t value )
{
    this->part_id_ = value;
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

void BlockMeta::RemoveNode( size_t session_id )
{
    for ( auto p = this->node_list_.begin(); p != this->node_list_.end(); p++ )
    {
        if ( ( *p )->Session()->Id() == session_id )
        {
            this->node_list_.erase( p );
            break;
        }
    }

    if ( this->node_list_.size() == 0 )
    {
        this->parent_->RemoveBlock( this->shared_from_this() );
    }
}

size_t BlockMeta::NodeCount()
{
    return this->node_list_.size();
}

sptr<NodeMeta> BlockMeta::FindNode( size_t session_id )
{
    for ( auto & n : this->node_list_ )
    {
        if ( n->Session()->Id() == session_id )
        {
            return n;
        }
    }

    return nullptr;
}

sptr<NodeMeta> BlockMeta::IdleNode()
{
    sptr<NodeMeta> result = nullptr;

    for ( auto & b : this->node_list_ )
    {
        if ( result == nullptr ||
             result->Session()->BlockCount() > b->Session()->BlockCount() )
        {
            result = b;
        }
    }

    return result;
}

sptr<FileMeta> BlockMeta::Parent()
{
    return this->parent_;
}

void BlockMeta::Parent( sptr<FileMeta> parent )
{
    this->parent_ = parent;
}

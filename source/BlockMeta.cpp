#include "BlockMeta.h"

size_t BlockMeta::Index()
{
    return this->index_;
}

void BlockMeta::Index( size_t value )
{
    this->index_ = value;
}

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

#include <FileMeta.h>

void FileMeta::FilePath( sptr<Path> value )
{
    this->path_ = value;
    this->name_ = value->FileName();
}

bool FileMeta::Open( string token )
{
    if ( this->is_open_ )
        return false;

    this->is_open_ = true;
    this->owner_token_ = token;
    return true;
}

bool FileMeta::Close( string token )
{
    if ( this->owner_token_ == token )
    {
        this->is_open_ = false;
        this->owner_token_ = "";
        return true;
    }

    return false;
}

bool FileMeta::AddBlock( sptr<BlockMeta> block )
{
    for ( auto & b : this->block_list_ )
    {
        if ( b->PartId() == block->PartId() )
        {
            return false;
        }
    }

    this->block_list_.push_back( move_ptr( block ) );
    this->size_ += block->BlockSize();

    return true;
}

bool FileMeta::RemoveBlock( sptr<BlockMeta> block )
{
    for ( auto  i = this->block_list_.begin();
                i != this->block_list_.end();
                i++ )
    {
        if ( ( *i )->PartId() == block->PartId() )
        {
            this->block_list_.erase( i );
            return true;
        }
    }

    return false;
} 

sptr<BlockMeta> FileMeta::FindBlock( size_t block_id )
{
    for ( auto & block : this->block_list_ )
    {
        if ( block_id == block->PartId() )
        {
            return block;
        }
    }
    
    return nullptr;
}

vector<sptr<BlockMeta>> FileMeta::BlockRange( size_t offset , size_t size )
{
    size_t                  cur_size = 0;
    vector<sptr<BlockMeta>> ret;

    for ( auto & b : this->block_list_ )
    {
        if ( offset <= cur_size )
        {
            ret.push_back( b );
        }

        if ( size <= cur_size )
        {
            return ret;
        }

        cur_size += b->Size();
    }

    return ret;
}

vector<sptr<BlockMeta>> FileMeta::BlockList()
{
    return vector<sptr<BlockMeta>>( this->block_list_ );
}

#include <FileDispatcher.h>
#include <FileDictionary.h>
#include <math.h>

size_t FileDispatcher::DispatchWrite( sptr<ClientToken> token , 
                                                       size_t offset , 
                                                       size_t size )
{
    auto path =  make_sptr( Path , token->Path() );
    auto meta = FileDictionary::Instance()->FindFile( path );

    if ( meta == nullptr )
    {
        //meta  = FileDictionary::Instance()->FindFile( path );
        return 0;
    }

    size_t front        = offset;
    size_t tail         = offset + size;
    size_t blocks_size  = 0;
    auto blocks         = meta->BlockList();

    for ( auto & b : blocks )
    {
        blocks_size += b->BlockSize();
    }

    if ( tail > blocks_size )
    {
        auto range = meta->BlockRange( offset , blocks_size );
        size_t delta = tail - blocks_size;
        auto num = scast<size_t>( std::ceil( (double)delta / (double)BLOCK_SIZE ) );
        return range.size() + num;
    }
    else
    {
        auto range = meta->BlockRange( offset , size );
        return range.size();
    }
}

FileDispatcher::FileDispatcher()
{

}

FileDispatcher::~FileDispatcher()
{
    
}

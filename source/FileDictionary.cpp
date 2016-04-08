#include <FileDictionary.h>
#include <BlockMeta.h>
#include <NodeMeta.h>

void FileDictionary::AddBlockMeta( NodeSession * session , 
                                   const MessageBlockMeta & message )
{
    sptr<FileMeta>  fileMeta = make_sptr( FileMeta );
    sptr<BlockMeta> block    = nullptr;
    sptr<NodeMeta>  node     = nullptr;

    auto path = make_sptr( Path , message.path() );
    auto file = this->director_->FindFile( path );

    if ( file == nullptr )
    {
        file = make_sptr( FileMeta );
        file->FilePath( path );
        this->director_->AddFile( file );
    }

    block = file->FindBlock( message.partid() );

    if ( block == nullptr )
    {
        block = make_sptr( BlockMeta );
    }

    block->PartId       ( message.partid() );
    block->BlockSize    ( 0 );
    block->FileOffset   ( message.fileoffset() );
    block->Size         ( message.size() );
    block->Parent       ( file );
    file->AddBlock      ( block );

    node = block->FindNode( session->Id() );

    if ( node == nullptr )
    {
        node = make_sptr( NodeMeta , message.index() , session );
        block->AddNode( node );
    }

    session->AddBlock( block );
}

sptr<FileMeta> FileDictionary::FindFile( sptr<Path> path )
{
    return this->director_->FindFile( path );
}

sptr<FileMeta> FileDictionary::CreateFile( sptr<Path> path )
{
    sptr<FileMeta> file = make_sptr( FileMeta );
    file->FilePath( path );

    this->director_->AddFile( file );
    return file;
}

sptr<DirectorMeta> FileDictionary::FindDir( string path )
{
    auto dir = this->director_->FindDirector( make_sptr( Path , path ) );
    return dir;
}

FileDictionary::FileDictionary()
{
    this->director_ = make_sptr( DirectorMeta );
}

FileDictionary::~FileDictionary()
{

}

#include <ClientSession.h>
#include <MessageBlockList.pb.h>
#include <MessageDeleteFileACK.pb.h>

void ClientSession::OpenFile( sptr<FileMeta> file )
{
    this->opened_file_ = file;
}

void ClientSession::CloseFile()
{
    if ( this->opened_file_ == nullptr )
    {
        return;
    }

    if ( this->open_token_ == nullptr )
    {
        return;
    }

    this->opened_file_->Close( this->open_token_->Token() );
}

void ClientSession::SetState( ClientState state )
{
    this->state_ = state;
}

void ClientSession::SetBlockNum( size_t num )
{
    this->block_total_num_ = num;
}

void ClientSession::AddBlock( uptr<MessagePrepareReadACK> ack )
{
    this->read_block_list_.push_back( move_ptr( ack ) );

    if ( this->read_block_list_.size() == this->block_total_num_ )
    {
        uptr<MessageBlockList> msg = make_uptr( MessageBlockList );
        msg->set_blockcount( (int)this->read_block_list_.size() );
        
        for ( auto & block : this->read_block_list_ )
        {
            msg->add_token      ( block->token() );
            msg->add_ip         ( block->address() );
            msg->add_port       ( block->port() );
            msg->add_fileoffset ( block->fileoffset() );
            msg->add_partid     ( block->partid() );
            msg->add_size       ( block->size() );
        }

        this->SendMessage( move_ptr( msg ) );
        this->read_block_list_.clear();
        this->Close();
    }
}
void ClientSession::AddBlock( uptr<MessagePrepareWriteACK> ack )
{ 
    this->write_block_list_.push_back( move_ptr( ack ) );
    
    if ( this->write_block_list_.size() == this->block_total_num_ )
    {
        uptr<MessageBlockList> msg = make_uptr( MessageBlockList );
        msg->set_blockcount( (int)this->write_block_list_.size() );
        
        for ( auto & block : this->write_block_list_ )
        {
            msg->add_token      ( block->token() );
            msg->add_ip         ( block->address() );
            msg->add_port       ( block->port() );
            msg->add_fileoffset ( block->fileoffset() );
            msg->add_partid     ( block->partid() );
            msg->add_size       ( block->size() );
        }

        this->SendMessage( move_ptr( msg ) );
        this->write_block_list_.clear();
        this->Close();
    }

}

void ClientSession::AddBlock( uptr<MessageDeleteBlockACK> ack )
{
    this->delete_block_list_.push_back( move_ptr( ack ) );
    
    if ( this->delete_block_list_.size() == this->block_total_num_ )
    {
        
        uptr<MessageDeleteFileACK> msg = make_uptr( MessageDeleteFileACK );
        msg->set_code( 0 );
        msg->set_message( "" );
        msg->set_path( ack->path() );
        this->SendMessage( move_ptr( msg ) );

        this->delete_block_list_.clear();
        this->Close();
    }
}


void ClientSession::OnClose()
{
    
}
 
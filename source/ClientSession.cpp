#include <ClientSession.h>
#include <MessageBlockList.pb.h>

void ClientSession::SetState( ClientState state )
{
    this->state_ = state;
}

void ClientSession::SetBlockNum( size_t num )
{
    this->block_total_num_ = num;
}

void ClientSession::AddBlock( uptr<MessagePrepareWriteACK> ack )
{
    this->block_list_.push_back( move_ptr( ack ) );

    if ( this->block_list_.size() == this->block_total_num_ )
    {
        uptr<MessageBlockList> msg = make_uptr( MessageBlockList );
        
        for ( auto & block : this->block_list_ )
        {
            msg->add_fileoffset ( block->block().fileoffset() );
            msg->add_partid     ( block->block().partid() );
            msg->add_size       ( block->block().size() );
            msg->add_token      ( block->token() );
            msg->add_ip         ( block->address() );
            msg->add_port       ( block->port() );
        }

        this->SendMessage( move_ptr( msg ) );

        this->block_list_.clear();

        this->Close();
    }

}
 
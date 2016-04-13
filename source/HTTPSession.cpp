#include <HTTPSession.h> 
#include <Json.hpp>
#include <NodeSessionPool.h>
#include <HTTPRouter.h>

using nlohmann::json;

HTTPSession::HTTPSession()
{
    this->request_ = make_sptr( HTTPRequest );
    this->router_  = make_sptr( HTTPRouter );
}

HTTPSession::~HTTPSession()
{
}

void HTTPSession::OnRead( uptr<Buffer> data )
{
    request_->Parse( move_ptr( data ) );

    if ( request_->Finish() || request_->ContentLength() == 0 )
    {
        Logger::Log( "HTTP % request %", 
                     this->ip_address() , 
                     request_->RequestUrl() );

        auto reponse_ = make_sptr( HTTPResponse );
        this->router_->Route( this ,
                              this->request_ ,
                              reponse_ );

        auto header_data = reponse_->BuildHeader();
        auto body_data = reponse_->BuildBody();

        if ( header_data != nullptr &&
             header_data->Size() != 0 )
        {
            this->Send( move_ptr( reponse_->BuildHeader() ) );
        }

        if ( body_data != nullptr &&
             body_data->Size() != 0 )
        {
            this->Send( move_ptr( reponse_->BuildBody() ) );
        }

        this->Close();
    }
}
 
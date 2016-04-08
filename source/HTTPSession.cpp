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
        auto reponse_ = make_sptr( HTTPResponse );
        this->router_->Route( this ,
                              this->request_ ,
                              reponse_ );
        this->Send( move_ptr( reponse_->BuildHeader() ) );
        this->Send( move_ptr( reponse_->BuildBody() ) );

        this->Close();
    }
}
 
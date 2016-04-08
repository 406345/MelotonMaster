#include <HTTPSession.h> 
#include <Json.hpp>
#include <NodeSessionPool.h>

using nlohmann::json;

HTTPSession::HTTPSession()
{
    this->request_ = make_sptr( HTTPRequest );
}

HTTPSession::~HTTPSession()
{
}

void HTTPSession::OnRead( uptr<Buffer> data )
{
    request_->Parse( move_ptr( data ) );

    if ( request_->Finish() || request_->ContentLength() == 0 )
    {
        auto rep = make_sptr( HTTPResponse );
        rep->Status( 200 );
        rep->Content( make_uptr(Buffer, "") );

        this->OnRequest( request_ , rep);
         
        auto header = rep->BuildHeader();
        auto body   = rep->BuildBody();

        this->Send( move_ptr( header ) );
        this->Send( move_ptr( body ) );

        this->Close();
    }
}

void HTTPSession::OnRequest( sptr<HTTPRequest> request , sptr<HTTPResponse> response )
{
    json obj;

    if ( request->RequestUrl() == "/v1/nodes/" )
    {
        NodeSessionPool::Instance()->Each( [ &obj ] ( NodeSession* node ) { 
            json jnode;
            jnode["cpu"] = node->CPU();
            jnode["memory"] = node->Memory();
            jnode["alive"] = node->AliveTime();
            jnode["blockcount"] = node->BlockCount();
            jnode["address"] = node->ip_address();
            obj.push_back( jnode );
        } );

    }

    response->Content( make_uptr( Buffer , obj.dump() ) );
}

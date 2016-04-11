#include <HTTPRouter.h>

#include <HTTPRouterHandler.h>

HTTPRouter::HTTPRouter( )
{
    this->Register( "/v1/node" ,   HTTPHandlerNode );
    this->Register( "/v1/file" ,    HTTPHandlerFile );
    this->Register( "/v1/dir" ,     HTTPHandlerDir );
    this->Register( "/v1/status" ,  HTTPHandlerNode );
}

HTTPRouter::~HTTPRouter( )
{
}

void HTTPRouter::Route( HTTPSession * session , 
                        sptr<HTTPRequest> request , 
                        sptr<HTTPResponse> response )
{
    auto uri  = request->Uri();
    auto call = this->router_[uri->Path()];

    if ( call != nullptr )
    {
        response->Status( 200 );
        call( session , request , response );
    }
    else
    {
        response->Status( 404 );
        response->Content( make_uptr( Buffer , "Request url is not found" ) );
    }
}

void HTTPRouter::Register( string url , router_handler_t call )
{
    if ( url.empty( ) )
        return;

    this->router_[url] = call;
}
 
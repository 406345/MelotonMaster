#include <HTTPListener.h>

Session * HTTPListener::CreateSession()
{
    return new HTTPSession();
}

void HTTPListener::OnSessionOpen( Session * session )
{

}

void HTTPListener::OnSessionClose( Session * session )
{
    SAFE_DELETE( session );
}

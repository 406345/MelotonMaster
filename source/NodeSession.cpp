#include <NodeSession.h>

void NodeSession::UpdateAliveTime()
{
    this->alive_time_ = Timer::Tick();
}

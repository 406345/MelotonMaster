#include <FileDispatcher.h>

FileDispatcher::FileDispatcher()
{
    dir_root_ = make_sptr( DirectorMeta );
}

FileDispatcher::~FileDispatcher()
{

}

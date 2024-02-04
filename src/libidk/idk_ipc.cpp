#include "idk_ipc.hpp"
#include "idk_platform.hpp"

#ifdef IDK_UNIX
    #include <unistd.h>
#elif defined(IDK_WINDOWS)
    #error Pls dont forget this lmao.
#endif


int idk::fork()
{
    return fork();
}


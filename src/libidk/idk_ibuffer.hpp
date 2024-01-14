#pragma once

#include <cstdint>
#include <cstddef>

namespace idk
{
    class iBuffer;
};


class idk::iBuffer
{
public:
    virtual        ~iBuffer() = default;

    virtual void *  data     (        ) = 0;
    virtual size_t  size     (        ) = 0;
    virtual size_t  typesize (        ) = 0;
    virtual size_t  nbytes   (        ) = 0;
    virtual void    resize   ( size_t ) = 0;   

};


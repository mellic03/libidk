#include "common.hpp"
#include <cstdlib>


#ifdef IDK_MEMORY_PROFILE

size_t IDK_MEMORY_PROFILE_TOTAL_ALLOCATION = 0;

void *operator new ( std::size_t n )
{
    IDK_MEMORY_PROFILE_TOTAL_ALLOCATION += n;
    return std::malloc(n);
}

void operator delete ( void *p ) throw()
{
    std::free(p);
}


void *operator new[] ( std::size_t n )
{
    IDK_MEMORY_PROFILE_TOTAL_ALLOCATION += n;
    return std::malloc(n);
}

void operator delete[] ( void *p ) throw()
{
    std::free(p);
}
#endif




uint8_t* idk::internal::baseptrs   [AllocatorType::ALLOC_NUM_TYPES];
size_t   idk::internal::tails      [AllocatorType::ALLOC_NUM_TYPES];
size_t   idk::internal::capacities [AllocatorType::ALLOC_NUM_TYPES];



static bool idk_memory_init()
{
    using namespace idk::internal;

    for (uint32_t i=0; i<AllocatorType::ALLOC_NUM_TYPES; i++)
    {
        capacities[i] = 128 * idk::KILO;
        baseptrs[i]   = (uint8_t *)malloc(capacities[i]);
        tails[i]      = 0;
    }

    return true;
}


bool idk::internal::initialized = idk_memory_init();




uint8_t *&
idk::internal::memory_baseptr( uint32_t type )
{
    return baseptrs[type];
}


size_t &
idk::internal::memory_tail( uint32_t type )
{
    return tails[type];
}


size_t    
idk::internal::memory_capacity( uint32_t type )
{
    return capacities[type];
}


size_t    
idk::internal::memory_usage( uint32_t type )
{
    return tails[type];
}





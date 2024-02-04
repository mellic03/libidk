#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>
#include "idk_alloc_assert.hpp"


#ifdef IDK_MEMORY_PROFILE
extern size_t IDK_MEMORY_PROFILE_TOTAL_ALLOCATION;
#endif

namespace idk
{
    static constexpr size_t KILO = 1024*1;
    static constexpr size_t MEGA = 1024*KILO;
};


namespace idk::internal
{
    enum AllocatorType: uint32_t
    {
        ALLOC_FRAME = 0,
        ALLOC_LINEAR,
        ALLOC_STACK,
        ALLOC_HEAP,

        ALLOC_NUM_TYPES
    };

    extern uint8_t* baseptrs   [ALLOC_NUM_TYPES];
    extern size_t   tails      [ALLOC_NUM_TYPES];
    extern size_t   capacities [ALLOC_NUM_TYPES];
    extern bool     initialized;


    uint8_t *&memory_baseptr  ( uint32_t type );
    size_t   &memory_tail     ( uint32_t type );
    size_t    memory_capacity ( uint32_t type );
    size_t    memory_usage    ( uint32_t type );


};

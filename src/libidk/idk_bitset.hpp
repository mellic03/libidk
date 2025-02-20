#pragma once

#include <cstdint>
#include <cstddef>


namespace idk
{
    class Bitset;
}


class idk::Bitset
{
private:
    uint64_t bits;

public:
    Bitset(): bits(0) {  }

    constexpr bool get        ( uint32_t i ) { return bits & (uint32_t(1) << i); }
    constexpr void set        ( uint32_t i ) { bits |=  (uint32_t(1) << i);      }
    constexpr void unset      ( uint32_t i ) { bits &= ~(uint32_t(1) << i);      }
    constexpr void toggle     ( uint32_t i ) { bits ^=  (uint32_t(1) << i);      }
    constexpr bool operator[] ( uint32_t i ) { return get(i);                    }

};


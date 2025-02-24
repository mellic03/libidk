#pragma once
#include "common.hpp"
#include "base_allocator.hpp"

// namespace idk
// {
//     class allocated_object
//     {
//     private:
    
//     public:
//         inline static idk::base_allocator *allocator = nullptr;
//         void *operator new( size_t );
//         void  operator delete( void* );
        
//     };
// }


#define IDK_MEMORY_MAKE_ALLOCATED(__classname__)\
    inline static idk::base_allocator *allocator = nullptr; \
    void *operator new( size_t nbytes ) \
    { \
        return __classname__::allocator->alloc(nbytes, alignof(##__classname__)); \
    } \
    void operator delete( void *ptr ) \
    { \
        __classname__::allocator->free(ptr); \
    } \


#pragma once

#include "memory/idk_memory.hpp"


// #include <cstdint>
// #include <cstddef>


// namespace idk
// {
//     class linear_allocator;
//     class frame_allocator;

//     class block_allocator;
//     class stdlib_allocator;

//     class MemorySystem
//     {
//         void update();
//     };

// }



// class idk::frame_allocator
// {
// private:
//     static uint8_t *baseptr;
//     static size_t   tail;
//     static size_t   capacity;

// public:
//     void *allocate( size_t nbytes );
//     void  deallocate( void * ) {  };

//     static void  reset() { tail = 0; };

// };



// class idk::linear_allocator
// {
// private:
//     static uint8_t *baseptr;
//     static size_t   tail;
//     static size_t   capacity;

// public:
//     void *allocate( size_t nbytes );
//     void  deallocate( void * ) {  };

// };



// // class idk::block_allocator
// // {
// // private:
// //     static uint8_t *baseptr;
// //     static size_t   tail;
// //     static size_t   capacity;

// // public:
// //     void *allocate( size_t nbytes );
// //     void  deallocate( void * );

// // };



// class idk::stdlib_allocator
// {
// public:
//     void *allocate( size_t nbytes );
//     void  deallocate( void * );
// };



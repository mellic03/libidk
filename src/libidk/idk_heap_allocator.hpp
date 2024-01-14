// #pragma once
// #include <cstdlib>


// namespace idk
// {
//     template <typename T>
//     class HeapAllocator;
// };



// template <typename T>
// class idk::HeapAllocator
// {
// private:
//     static constexpr size_t INITIAL_SIZE = 4;

//     T *     m_data;
//     size_t  m_size;
//     size_t  m_cap;


// public:
//             HeapAllocator();
//            ~HeapAllocator();

//     T *     alloc( size_t nbytes );
//     void    realloc( size_t cap );
//     void    free( T * );

// };



// template <typename T>
// idk::HeapAllocator<T>::HeapAllocator()
// :   m_size(INITIAL_SIZE),
//     m_cap(INITIAL_SIZE)
// {
//     m_data = (T *)malloc(INITIAL_SIZE * sizeof(T));
// }


// template <typename T>
// void
// idk::HeapAllocator<T>::realloc( size_t cap )
// {
    
// }


// template <typename T>
// idk::HeapAllocator<T>::~HeapAllocator()
// {
//     free(m_data);
// }



// template <typename T>
// T *
// idk::HeapAllocator<T>::alloc( size_t nbytes )
// {
    
// }



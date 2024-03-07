// #pragma once

// #include "idk_vector.hpp"
// #include "idk_assert.hpp"
// #include <cstring>


// template <typename T, typename alloc_type>
// void
// idk::vector<T, alloc_type>::_realloc( size_t capacity )
// {
//     T *new_data = m_allocator.allocate(capacity);

//     std::memcpy(new_data, m_data, std::min(m_cap, capacity));
//     m_allocator.deallocate(m_data, m_cap);

//     m_data = new_data;
//     m_cap  = capacity;
// }




// template <typename T, typename alloc_type>
// idk::vector<T, alloc_type>::vector()
// :   m_size(0),
//     m_cap(DEFAULT_CAP)
// {
//     m_data = m_allocator.allocate(DEFAULT_CAP);
// }



// template <typename T, typename alloc_type>
// idk::vector<T, alloc_type>::vector( size_t size )
// :   m_size(size),
//     m_cap(size)
// {
//     m_data = m_allocator.allocate(size);
// }



// template <typename T, typename alloc_type>
// idk::vector<T, alloc_type>::vector( size_t size, const T &data )
// :   m_size(size),
//     m_cap(size)
// {
//     m_data = m_allocator.allocate(size);

//     for (size_t i=0; i<size; i++)
//     {
//         m_data[i] = data;
//     }
// }




// template <typename T, typename alloc_type>
// void
// idk::vector<T, alloc_type>::resize( size_t sz )
// {
//     m_size = sz;

//     if (m_size >= m_cap)
//     {
//         this->_realloc(sz);
//     }
// }



// template <typename T, typename alloc_type>
// void
// idk::vector<T, alloc_type>::push_back( const T &data )
// {
//     if (m_size + 1 >= m_cap)
//     {
//         this->_realloc(2*m_size);
//     }

//     m_data[m_size] = data;
//     m_size += 1;
// }


// template <typename T, typename alloc_type>
// void
// idk::vector<T, alloc_type>::pop_back()
// {
//     m_size -= 1;
//     IDK_ASSERT("RUH ROH", m_size >= 0);
// }


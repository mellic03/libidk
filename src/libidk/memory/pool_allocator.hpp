// #pragma once
// #include "common.hpp"
// #include "base_allocator.hpp"
// #include "fixed_vector.hpp"
// #include "../idk_log.hpp"


// namespace idk
// {
//     template <typename T>
//     class pool_allocator;
// }


// template <typename T>
// class idk::pool_allocator: public idk::templated_allocator<T>
// {
// private:
//     fixed_vector<bool>   m_active;
//     fixed_vector<size_t> m_skip;
//     fixed_vector<size_t> m_rskip;
//     fixed_vector<T>      m_data;
//     fixed_vector<size_t> m_freelist;

//     T *_alloc()
//     {
//         return static_cast<T*>(this->alloc(sizeof(T), alignof(T)));
//     }

//     void _free( T *ptr )
//     {
//         this.
//         return static_cast<T*>(this->alloc(sizeof(T), alignof(T)));
//     }

// public:
//     pool_allocator( size_t capacity, base_allocator *A );

//     virtual void *alloc( size_t nbytes, size_t alignment ) final;
//     virtual T    *alloc( size_t count ) final;
//     virtual void  free( void* ) final;
//     virtual void  clear() final;

//     int  create();
//     // int  create( const T &data );
//     // int  create( T &&data );
//     // T&   get( int id );
//     void destroy( int id );

//     // bool contains( int id )
//     // {
//     //     if (id < 0 || id >= m_forward.size())
//     //     {
//     //         return false;
//     //     }

//     //     return m_forward[id] != -1;
//     // }

// };


// template <typename T>
// idk::pool_allocator<T>::pool_allocator( size_t capacity, base_allocator *A )
// :   m_active    (capacity, false, A),
//     m_skip      (capacity, 1, A),
//     m_rskip     (capacity, 1, A),
//     m_data      (capacity, A),
//     m_freelist  (capacity, A)
// {
//     for (int i=capacity-1; i>=0; i--)
//     {
//         m_freelist.push(i);
//     }
// }


// template <typename T>
// void*
// idk::pool_allocator<T>::alloc( size_t nbytes, size_t alignment )
// {
//     T *ptr = static_cast<T*>(p);
    
//     // m_freelist.push(static_cast<int>(ptr - m_base));
// }


// template <typename T>
// void
// idk::pool_allocator<T>::free( void *p )
// {
//     T *ptr = static_cast<T*>(p);
    
//     // m_freelist.push(static_cast<int>(ptr - m_base));
// }



// // template <typename T>
// // void
// // idk::pool_allocator<T>::clear()
// // {


// // }




// template <typename T>
// int idk::pool_allocator<T>::create()
// {
//     LOG_ASSERT(m_freelist.empty() == false, "Allocation failed: pool full");

//     size_t idx;

//     if (m_freelist.empty())
//     {
//         idx = m_data.size() - 1;
//     }

//     else
//     {
//         idx = m_freelist.top();
//         m_freelist.pop();
//     }

//     if (idx > 0)
//         m_skip[idx-1] = 1;

//     if (idx < m_data.size() - 1)
//         m_rskip[idx+1] = 1;

//     m_active[idx] = true;

//     T *ptr = static_cast<T*>(&(m_data[idx]));
//     std::construct_at(ptr);

//     return idx;
// }


// // template <typename T>
// // T& idk::pool_allocator<T>::get( int id )
// // {
// //     LOG_ASSERT(
// //         this->contains(id) == true,
// //         "Attempted access of non-existant object {}", id
// //     );

// //     return m_data[m_forward[id]];
// // }


// template <typename T>
// void idk::pool_allocator<T>::destroy( int id )
// {
//     LOG_ASSERT(
//         this->contains(id) == true,
//         "Attempted deletion of non-existant object {}", id
//     );

//     if (idx > 0)
//         m_skip[idx-1] = 2;

//     if (idx < m_data.size() - 1)
//         m_rskip[idx+1] = 2;

//     int idx = m_forward[id];

//     if (idx != m_data.size() - 1)
//     {
//         m_data[idx] = std::move(m_data.back());
//     }


// }


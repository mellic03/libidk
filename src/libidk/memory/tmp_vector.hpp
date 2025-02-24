// #pragma once
// #include "cringe_ptr.hpp"
// #include "stack_allocator.hpp"
// #include "../idk_log.hpp"

// namespace idk
// {
//     template <typename T>
//     class tmp_vector;

//     namespace memory
//     {
//         extern idk::stack_allocator *stack;
//     }
// }


// template <typename T>
// class idk::tmp_vector
// {
// private:
//     size_t m_size, m_cap;
//     idk::cringe_ptr<T> m_ptr;
//     T *m_data;

// public:

//     tmp_vector( size_t sz, size_t cap )
//     :   m_size (sz),
//         m_cap  (cap),
//         m_ptr  (cap, memory::stack)
//     {
//         m_data = m_ptr.get();
//     }

//     ~tmp_vector()
//     {

//     }

//     void push( const T &X )
//     {
//         // IDK_ASSERT("size must be < capacity", m_size < m_cap);
//         m_data[m_size++] = X;
//     }

//     void pop()
//     {
//         this->back().~T();
//         m_size--;
//     }

//     constexpr T *data() noexcept { return m_ptr.get(); }

//     constexpr T &front() noexcept { return m_data[0]; }
//     constexpr T &back() noexcept { return m_data[m_size-1]; }
//     constexpr T &front() const noexcept { return front(); }
//     constexpr T &back() const noexcept { return back(); }

//     constexpr size_t size() const { return m_size; } 

//     T &operator[] ( int i ) { return m_data[i]; }
//     const T &operator[] ( int i ) const { return m_data[i]; }
// };


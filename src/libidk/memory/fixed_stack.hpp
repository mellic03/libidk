// #pragma once
// #include "base_allocator.hpp"
// #include "../idk_log.hpp"

// namespace idk
// {
//     template <typename T>
//     class fixed_stack;
// }


// template <typename T>
// class idk::fixed_stack
// {
// protected:
//     base_allocator *m_allocator;
//     size_t m_cap;
//     T *m_base;
//     T *m_top;
//     T *m_end;

// public:
//     fixed_stack( size_t capacity, base_allocator *A )
//     :   m_allocator(A)
//     {
//         m_cap  = capacity;
//         m_base = static_cast<T*>(A->alloc(capacity*sizeof(T), alignof(T)));
//         m_top  = m_base;
//         m_end  = m_base + capacity;
//         // std::cout << "---------------fixed_stack-------------------\n"
//         //           << "base, cap, end:  " << uint64_t(m_base) << ", " << uint64_t(capacity) << ", " << uint64_t(m_top)
//         //           << "\n----------------------------------------------\n"; 
//         // LOG_INFO("base={}, cap={}", m_base, capacity);
//     }

//     fixed_stack( size_t capacity, const T &value, base_allocator *A )
//     :   fixed_stack(capacity, A)
//     {
//         for (size_t i=0; i<capacity; i++)
//         {
//             m_base[i] = value;
//         }
//     }

//     ~fixed_stack()
//     {
//         // m_allocator->free(m_base);
//     }

//     fixed_stack(const fixed_stack &) = delete; // Disable copy constructor
//     fixed_stack &operator=(const fixed_stack &) = delete; // Disable assignment

//     void push( const T &data )
//     {
//         *(m_top++) = data;
//     }

//     void push( T &&data )
//     {
//         *(m_top++) = std::move(data);
//     }

//     void pop()
//     {
//         m_top--;
            
//         if constexpr (!std::is_pointer_v<T>)
//         {
//             (*m_top).~T();
//         }
//     }

//     T&       top() { return *(m_top - 1); }
//     const T& top() const { return *(m_top - 1); }

//     size_t   size()  const { return static_cast<size_t>(m_top - m_base); }
//     bool     empty() const { return m_top == m_base; }

//     struct iterator;
//     iterator begin() { return iterator(m_base); };
//     iterator end()   { return iterator(m_top);  };
// };



// template <typename T>
// struct idk::fixed_stack<T>::iterator
// {
//     T *ptr;

//     iterator( T *p )                 : ptr(p)         {  };
//     iterator( const iterator &other ): ptr(other.ptr) {  };

//     iterator &operator ++ ()
//     {
//         ptr++;
//         return *this;
//     };

//     iterator operator ++ (int)
//     {
//         return iterator(ptr++);
//     };

//     bool operator == ( const iterator &rhs ) { return ptr == rhs.ptr; };
//     bool operator != ( const iterator &rhs ) { return ptr != rhs.ptr; };
//     T &operator * () { return *ptr; };

// };
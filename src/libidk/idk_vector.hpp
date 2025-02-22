#pragma once

#include "idk_pod.hpp"

#include <vector>
#include <fstream>


namespace idk
{
    template <typename T, typename A = std::allocator<T>>
    using vector = std::vector<T, A>;

    // template <typename T>
    // using tvector = std::vector<T, idk::frame_allocator<T>>;

    // template <typename T>
    // using pvector = std::vector<T, idk::linear_allocator<T>>;

};




template <typename T, typename A>
std::ofstream &operator << ( std::ofstream &stream, const idk::vector<T, A> &v )
{
    uint32_t num_elements = v.size();
    stream.write(reinterpret_cast<const char *>(&num_elements), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char *>(v.data()), v.size()*sizeof(T));
    return stream;
}


template <typename T, typename A>
void operator >> ( std::ifstream &stream, idk::vector<T, A> &v )
{
    uint32_t num_elements;
    stream.read(reinterpret_cast<char *>(&num_elements), sizeof(uint32_t));

    v.resize(num_elements);
    stream.read(reinterpret_cast<char *>(v.data()), v.size()*sizeof(T));
}







// template <typename T, typename alloc_type = std::allocator<T>>
// class idk::vector: public idk::iBuffer
// {
// protected:
//     alloc_type m_allocator;
//     T *m_data;

// private:
//     static constexpr size_t DEFAULT_CAP = 4;
//     size_t      m_size;
//     size_t      m_cap;

//     void        _realloc( size_t size );


// public:
//                 vector();
//                 vector( size_t size );
//                 vector( size_t size, const T &data );

//     size_t      capacity() const { return m_cap; };


//     // idk::iBuffer compliance
//     // -----------------------------------------------------------------------------------------
//     virtual void *  data()      final { return m_data;           };
//     virtual size_t  size()      final { return m_size;           };
//     virtual size_t  typesize()  final { return sizeof(T);        };
//     virtual size_t  nbytes()    final { return size()*sizeof(T); };
//     virtual void    resize( size_t s ) final;
//     // -----------------------------------------------------------------------------------------

//     void        push_back( const T &data );
//     void        pop_back();

//     const T&    front() const { return m_data[0];        };
//     const T&    back()  const { return m_data[m_size-1]; };

//     T&          operator [] ( int i ) { return m_data[i]; };
//     const T&    operator [] ( int i ) const { return m_data[i]; };


//     struct iterator;

//     iterator begin() { return iterator(&m_data[0]);          };
//     iterator end()   { return iterator(&m_data[0] + size()); };

// };



// template <typename T, typename alloc_type>
// struct idk::vector<T, alloc_type>::iterator
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



// #include "idk_vector.inl"



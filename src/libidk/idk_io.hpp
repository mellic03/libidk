#pragma once

#include <fstream>
#include <concepts>
#include <string>

#include <cstdint>


// namespace idk
// {
//     template <typename T>
//     concept IsNumeric = std::integral<T> or std::floating_point<T>;

//     template <typename A>
//     concept IsContainer = requires(A a, size_t size)
//     {
//         { a.data   (    ) };
//         { a.resize (size) };
//     };


//     template <typename T> requires IsNumeric<T>
//     void streamWrite( std::ofstream &, const T & );

//     template <typename T> requires IsContainer<T>
//     void streamWrite( std::ofstream &, const T & );

//     template <typename T> requires IsNumeric<T>
//     T streamRead( std::ifstream & );

//     template <typename T> requires IsContainer<T>
//     T streamRead( std::ifstream & );
// };



// template <typename T> requires idk::IsNumeric<T>
// void
// idk::streamWrite( std::ofstream &stream, const T &n )
// {
//     stream.write(reinterpret_cast<const char *>(&n), sizeof(n));
// }


// template <typename T> requires idk::IsContainer<T>
// void
// idk::streamWrite( std::ofstream &stream, const T &container )
// {
//     uint32_t n = uint32_t(container.size());
//     stream.write(reinterpret_cast<const char *>(&n), sizeof(uint32_t));
//     stream.write(reinterpret_cast<const char *>(container.data()), n * sizeof(typename T::value_type));
// }



// template <typename T> requires idk::IsNumeric<T>
// T
// idk::streamRead( std::ifstream &stream )
// {
//     T n;
//     stream.read(reinterpret_cast<char *>(&n), sizeof(T));
//     return n;
// }



// template <typename T> requires idk::IsContainer<T>
// T
// idk::streamRead( std::ifstream &stream )
// {
//     T container;

//     uint32_t n;
//     stream.read(reinterpret_cast<char *>(&n), sizeof(uint32_t));

//     container.resize(n);
//     stream.read(reinterpret_cast<char *>(container.data()), n*sizeof(typename T::value_type));

//     return container;
// }


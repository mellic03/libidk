#pragma once


#include "idk_io.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>

#include <cstring>



namespace idk
{
    template <size_t N>
    struct string_literal
    {
        char data[N];

        constexpr string_literal()
        {
            std::fill_n(data, N, '\0');
        };

        constexpr string_literal( const char (&str)[N] ): string_literal()
        {
            std::copy_n(str, N, data);
        };

        constexpr const char operator [] (int i) const { return data[i]; };
    };


    template <idk::string_literal str, size_t idx>
    constexpr void print();

    template <idk::string_literal str, size_t idx, typename T>
    constexpr void print( T first );

    template <idk::string_literal str, size_t idx, typename T, typename ...Args>
    constexpr void print( T first, Args ...args );

    template <idk::string_literal str, typename ...Args>
    constexpr void print( Args ...args );

};


template <idk::string_literal str, size_t idx>
constexpr void
idk::print()
{
    if constexpr (str[idx] == '\0')
    {
        return;
    }

    std::cout << str[idx];
    idk::print<str, idx+1>();
}

template <idk::string_literal str, size_t idx, typename T>
constexpr void
idk::print( T first )
{
    std::cout << first;
}



template <idk::string_literal str, size_t idx, typename T, typename ...Args>
constexpr void
idk::print( T first, Args ...args )
{
    if constexpr (str[idx] == '\0')
    {
        return;
    }

    else if (str[idx] == '{')
    {
        std::cout << first;
        idk::print<str, idx+2>(args...);
    }

    else
    {
        std::cout << str[idx];
        idk::print<str, idx+1>(first, args...);
    }

}




template <idk::string_literal str, typename ...Args>
constexpr void
idk::print( Args ...args )
{
    idk::print<str, 0>(args...);
}

















// #pragma once


// #include "idk_io.hpp"

// #include <iostream>
// #include <string>
// #include <vector>
// #include <array>
// #include <tuple>
// #include <algorithm>

// #include <cstring>



// namespace idk
// {
//     // template <int size>
//     struct literal
//     {
//         char data[64 + 2 + 1] {  };

//         constexpr literal()
//         {
//             for (auto i=0; i<64; i++)
//             {
//                 data[i] = '\0';
//             }
//         };

//         template <size_t size>
//         constexpr literal( const char (&str)[size] )
//         {
//             for (int i=0; i<size; i++)
//             {
//                 data[i] = str[i];
//             }
//         };


//         constexpr const char operator [] (int i) const { return data[i]; };
//     };


//     constexpr void base_print()
//     {
//         // std::cout << "Base case!\n";
//         return;
//     };

//     template <idk::literal format, size_t index, typename T>
//     constexpr void print( T last );

//     template <idk::literal format, size_t index, typename T, typename ...Args>
//     constexpr void print( T first, Args ...args );

//     // template <typename T, typename ...Args>
//     // constexpr int print( idk::literal<64> format, T first, Args ...args );
// };



// template <idk::literal format, size_t index, typename T>
// constexpr void
// idk::print( T last )
// {
//     std::cout << format.data[index] << " ";
//     idk::base_print();
// }



// template <idk::literal format, size_t index, typename T, typename ...Args>
// constexpr void
// idk::print( T first, Args ...rest )
// {
//     std::cout << format.data[index] << " ";

//     // if constexpr (format.data[0] == '{')
//     // {
//     //     std::cout << "WOOP!\n";
//     // }

//     // else if constexpr (format.data[0] == '}')
//     // {
//     //     std::cout << "WOOP!\n";
//     // }

//     // else
//     {
//         idk::print<format, index+1>(rest...);
//     }
// }



// // template <typename T, typename ...Args>
// // constexpr int
// // idk::print( idk::literal<64> format, T first, Args ...rest )
// // {


// //     // for (size_t i=0; i<format.length(); i++)
// //     // {
// //     //     if (format[i] == '{')
// //     //     {
// //     //         size_t left  = i+1;
// //     //         size_t right = format.find('}');
// //     //         // size_t idx   = std::stoul(format.substr(left, right-left));
// //     //         std::cout << std::get<idx>(arguments);
// //     //         i = right;
// //     //     }
// //     // }

// //     return 0;
// // }




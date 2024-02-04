#include "idk_io.hpp"


// static size_t
// num_format_specs( const char *format )
// {
//     size_t num_specifiers = 0;

//     for (char c: format)
//     {
//         if (c == '%')
//         {
//             num_specifiers += 1;
//         }
//     }

//     return num_specifiers;
// }



// static int
// is_specifier( const std::string &format, size_t idx )
// {
//     static std::string stack = "";
//     static bool pushing = false;

//     if (format[idx] == '{')
//     {
//         pushing = true;
//     }

//     else if (format[idx] == '}')
//     {
//         pushing = true;
//     }

//     else
//     {
//         stack.push_back(format[idx]);
//     }

//     return 1;
// }



// static void
// do_specifier( std::string &buffer, size_t idx )
// {

// }


// int
// idk::print( const std::string &format, ... )
// {
//     std::string buffer = format;

//     va_list args;
//     size_t num_specifiers = num_format_specs(format);

//     va_start( args, num_specifiers );

//     for (size_t i=0; i<buffer.length(); i++)
//     {
//         if (is_specifier(format, i))
//         {
//             buffer.insert()
//         }

//     }

//     while (*format)
//     {
//         if (*format == '%')
//         {
//             format += 1;
//             idk_internal_printf(*format, args);
//         }

//         else
//         {
//             system::terminal::putchar(*format);
//         }

//         format += 1;
//     }

//     va_end( args );

//     return 0;
// }


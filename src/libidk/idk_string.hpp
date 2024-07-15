#pragma once

#include <vector>

#include <string>
#include <cstdint>
#include <cstddef>
#include <fstream>


namespace idk
{
    // using string  = std::string;
    // using tstring = std::basic_string<char, std::char_traits<char>, idk::frame_allocator<char>>;
    // using pstring = std::basic_string<char, std::char_traits<char>, idk::linear_allocator<char>>;

    class string;
};



class idk::string
{
private:
    std::vector<uint8_t> m_data;

public:
    string() {  };


};



// inline std::ofstream &operator << ( std::ofstream &stream, const idk::string &str )
// {
//     uint32_t num_elements = str.size();
//     stream.write(reinterpret_cast<const char *>(&num_elements), sizeof(uint32_t));
//     stream.write(reinterpret_cast<const char *>(str.data()), str.size()*sizeof(char));
//     return stream;
// }


// inline void operator >> ( std::ifstream &stream, idk::string &str )
// {
//     uint32_t num_elements;
//     stream.read(reinterpret_cast<char *>(&num_elements), sizeof(uint32_t));

//     str.resize(num_elements);
//     stream.read(reinterpret_cast<char *>(str.data()), str.size()*sizeof(char));
// }

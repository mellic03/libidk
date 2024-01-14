#include "idk_file.hpp"
#include <fstream>
#include <sstream>


std::string
idk::loadfile( const std::string &filepath )
{
    std::stringstream buffer;
    buffer << std::ifstream(filepath).rdbuf();
    return buffer.str();
}


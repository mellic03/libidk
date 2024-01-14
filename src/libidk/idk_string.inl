#pragma once
#include "idk_string.hpp"


idk::string::string( const char *str )
:   vector()
{
    size_t len = strlen(str+1);
    this->resize(len);

    std::memcpy(m_data.get(), str, len);
}




std::ofstream &operator << ( std::ofstream &os, const idk::string &str )
{
    for (size_t i=0; i<str.size(); i++)
    {
        os << str[i];
    }

    return os;
}


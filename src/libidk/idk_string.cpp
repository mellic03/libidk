#include "idk_string.hpp"
#include <cstring>


idk::string::string( const char *ptr )
:   vector2(std::strlen(ptr)+1)
{
    uint64_t len = this->size();
    for (size_t i=0; i<len; i++)
    {
        (*this)[i] = ptr[i];
    }
}


idk::string&
idk::string::operator= ( const char *ptr )
{
    *this = idk::string(ptr);
    return *this;
}





bool
operator== ( const idk::string &lhs, const char *rhs )
{
    return std::strcmp(lhs.c_str(), rhs) == 0;   
}

bool
operator== ( const idk::string &lhs, const idk::string &rhs )
{
    return lhs == rhs.c_str();
}



std::ostream &operator << ( std::ostream &stream, const idk::string &str )
{
    for (int i=0; i<str.size(); i++)
        stream << str[i];
    return stream;
}


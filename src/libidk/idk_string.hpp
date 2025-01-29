#pragma once

#include <ostream>
#include "idk_vector2.hpp"

namespace idk
{
    class string;
};


class idk::string: public idk::vector2<char>
{
private:
    // idk::vector2<char> m_data;

public:
    string( const char* );
    string &operator= ( const char* );
    const char *c_str() { return (const char*)data(); }
    const char *c_str() const { return (const char*)data(); }

};


bool operator== ( const idk::string&, const char* );
bool operator== ( const idk::string&, const idk::string& );


std::ostream &operator << ( std::ostream &stream, const idk::string &str );


#pragma once
#include "idk_vector.hpp"


namespace idk { class string; };

class idk::string: public idk::vector<char>
{
private:

public:

        string();
        string( const idk::string & );
        string( const char * );

    const char *c_str() const { return m_data.get(); };

};

std::ofstream &operator << ( std::ofstream &, const idk::string & );

#include "idk_string.inl"


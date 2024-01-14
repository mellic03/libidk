#pragma once

#include <map>



namespace idk
{
    template <typename key_type, typename value_type, value_type default_value>
    class map;
};

template <typename key_type, typename value_type, value_type default_value>
class idk::map
{
private:
    struct DefaultValue
    {
        bool set = false;
        value_type value = default_value;
    };

    std::map<key_type, DefaultValue> m_map;


public:

    // void clear() { m_map.clear(); };

    value_type &operator [] ( int i ) { return m_map[i].value; };


};


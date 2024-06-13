#pragma once

#include <cstdint>
#include <cstddef>
#include <concepts>
#include <fstream>

#include <vector>

#include "idk_assert.hpp"


namespace idk
{
    template <typename T>
    concept is_explicitly_serializable = requires( T t, std::ofstream O, std::ifstream I )
    {
        { t.serialize(O)   };
        { t.deserialize(I) };
    };


    template <typename T>
    concept is_vector = requires( T t )
    {
        { t.size()  };
        { t.data()  };
        { t.begin() };
        { t.end()   };
    };


    template <typename T>
    concept is_set = requires( T t )
    {
        { t.size()  };
        { t.insert()  };
        { t.begin() };
        { t.end()   };
    };


    template <typename T>
    concept is_numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;


    template <typename T>
    size_t streamwrite( std::ofstream &stream, const T &data )
    {
        size_t n = 0;

        if constexpr (idk::is_explicitly_serializable<T>)
        {
            n += data.serialize(stream);
        }

        else if constexpr (idk::is_vector<T>)
        {
            uint32_t size = data.size();
            n += idk::streamwrite(stream, size);

            for (const auto &element: data)
            {
                n += idk::streamwrite(stream, element);
            }
        }

        else if constexpr (idk::is_set<T>)
        {
            uint32_t size = data.size();
            n += idk::streamwrite(stream, size);

            for (const auto &element: data)
            {
                n += idk::streamwrite(stream, element);
            }
        }

        else
        {
            stream.write(reinterpret_cast<const char *>(&data), sizeof(T));
            n += sizeof(T);
        }

        return n;
    }



    template <typename T>
    size_t streamread( std::ifstream &stream, T &data )
    {
        size_t n = 0;

        if constexpr (idk::is_explicitly_serializable<T>)
        {
            n += data.deserialize(stream);
        }

        else if constexpr (idk::is_vector<T>)
        {
            uint32_t size;
            n += idk::streamread(stream, size);
            data.resize(size);

            for (auto &element: data)
            {
                n += idk::streamread(stream, element);
            }
        }

        else if constexpr (idk::is_set<T>)
        {
            uint32_t size;
            n += idk::streamread(stream, size);
            // data.resize(size);

            // for (auto &element: data)
            for (uint32_t i=0; i<size; i++)
            {
                typename T::value_type element;
                n += idk::streamread(stream, element);
                data.insert(element);
            }
        }

        else
        {
            stream.read(reinterpret_cast<char *>(&data), sizeof(T));
            n += sizeof(T);
        }

        return n;
    }

};





#define IDK_STRUCT_TYPENAME float
#define IDK_STRUCT_BEGIN(name) struct name {
#define IDK_STRUCT_END(IDK_STRUCT_MEMBERS) };

#define IDK_STRUCT_WRITE(datatype, member, initial_value) n += idk::streamwrite<datatype>(stream, this->member);
#define IDK_STRUCT_READ(datatype, member, initial_value) n += idk::streamread<datatype>(stream, this->member);

#define IDK_STRUCT_DECLARE_MEMBER(datatype, name, initial_value) datatype name = initial_value;

#define IDK_STRUCT_BODY(IDK_STRUCT_MEMBERS) \
\
    IDK_STRUCT_MEMBERS(IDK_STRUCT_DECLARE_MEMBER) \
\
    size_t serialize( std::ofstream &stream ) const \
    { \
        size_t n = 0; \
        IDK_STRUCT_MEMBERS(IDK_STRUCT_WRITE) \
        return n; \
    }; \
\
    size_t deserialize( std::ifstream &stream ) \
    { \
        size_t n = 0; \
        IDK_STRUCT_MEMBERS(IDK_STRUCT_READ) \
        return n; \
    }; \
\



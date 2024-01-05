#pragma once

#include "idk_dynamiclib.hpp"


namespace idk
{
    class APILoader;
};



class idk::APILoader
{
private:
    void *m_lib;

public:
        APILoader( const char *path );

    template <typename return_type, typename ...Args>
    return_type *call( const char *symbol, Args ...args );

};



template <typename return_type, typename ...Args>
return_type *
idk::APILoader::call( const char *symbol, Args ...args )
{
    typedef return_type *(*functionptr_type)( Args... );
    void *ptr = idk::dynamiclib::loadFunction(m_lib, symbol);

    return (*(functionptr_type)(ptr))(args...);
};


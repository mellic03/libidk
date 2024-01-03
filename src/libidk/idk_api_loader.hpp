#pragma once

#include "idk_dynamiclib.hpp"



namespace idk { class APILoader; };

class idk::APILoader
{
private:
    void *m_lib;


public:
    APILoader( const char *path )
    {
        m_lib = idk::dynamiclib::loadObject(path);
    };

    ~APILoader()
    {
        idk::dynamiclib::unloadObject(m_lib);
    };

    void *function_ptr( const char *symbol )
    {
        return idk::dynamiclib::loadFunction(m_lib, symbol);
    };


    template <typename return_type, typename ...Args>
    return_type *function_call( const char *symbol, Args ...args );

};



template <typename return_type, typename ...Args>
return_type *
idk::APILoader::function_call( const char *symbol, Args ...args )
{
    typedef return_type *(*functionptr_type)( Args... );
    void *ptr = idk::dynamiclib::loadFunction(m_lib, symbol);

    return (*(functionptr_type)(ptr))(args...);
};


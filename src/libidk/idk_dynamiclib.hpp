#pragma once


namespace idk::dynamiclib
{
    void *loadObject( const char *filepath );
    void *loadFunction( void *lib, const char *symbol );
    void  unloadObject( void *lib );

    template <typename return_type, typename ...Args>
    return_type call( void *function_ptr, Args ...args );

};


template <typename return_type, typename ...Args>
return_type
idk::dynamiclib::call( void *function_ptr, Args ...args )
{
    typedef return_type (*functionptr_type)( Args... );
    return (*(functionptr_type)(function_ptr))(args...);
};


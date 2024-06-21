#pragma once

#include <string>


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




namespace idk
{
    class DynamicLoader;

    template <typename T>
    class GenericLoader;
};



class idk::DynamicLoader
{
private:
    std::string     m_realpath;
    std::string     m_temppath;

    void           *m_lib;
    void           *m_functionptr;
    void           *m_data;

    bool            m_loaded = false;
    bool            m_moved  = false;

    void            _load();
    void            _unload();
    bool            is_moved() { return m_moved; };


public:
                    DynamicLoader( const std::string &filepath );
                    DynamicLoader( const DynamicLoader & ) = delete;
                    DynamicLoader( DynamicLoader && );
                   ~DynamicLoader();

    DynamicLoader & operator = ( DynamicLoader && );

    bool            is_loaded() { return m_loaded; };
    void            reload();
    virtual void *  getData();

};



template <typename T>
class idk::GenericLoader: public idk::DynamicLoader
{
public:
            GenericLoader( const std::string &filepath )
            : DynamicLoader(filepath) {  };

    T *     getInstance() { return reinterpret_cast<T *>(getData()); };
};




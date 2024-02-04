#pragma once

#include "idk_api_loader.hpp"
#include <string>


namespace idk
{
    class EngineAPI;
    class RuntimeScript;
}


class idk::RuntimeScript
{
private:
    std::string m_name;
    std::string m_filepath;
    std::string m_libpath;

    void *      m_lib;
    void *      m_entry;
    bool        m_ready = false;

    void        _load( const std::string &filepath );
    void        _unload();


public:
    int         id = -1;

                RuntimeScript() {  };
                RuntimeScript( const std::string &filepath );
                RuntimeScript( const RuntimeScript & );
                RuntimeScript( RuntimeScript &&);
               ~RuntimeScript();

    RuntimeScript operator = ( const RuntimeScript &s );

    bool        is_ready() { return m_ready; };

    int         execute( idk::EngineAPI &, int obj_id, int other_id );
    void        reload();

    const std::string &name() { return m_name; };

};


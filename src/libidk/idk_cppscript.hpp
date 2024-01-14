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
    std::string m_filepath;
    std::string m_libpath;

    void *      m_lib;
    void *      m_entry;

    void        _load( const std::string &filepath );
    void        _unload();


public:
                RuntimeScript( const std::string &filepath );
               ~RuntimeScript();

    int         execute( idk::EngineAPI & );
    void        reload();

};


#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "idk_cppscript.hpp"
#include "idk_dynamiclib.hpp"


void
idk::RuntimeScript::_load( const std::string &filepath )
{
    m_filepath = filepath;

    std::filesystem::path path(filepath);
    m_libpath = "IDKGE/temp/" + path.relative_path().stem().string();

    std::string cmd = "clang -shared ";
                cmd += filepath;
                cmd += " -fPIC -o";
                cmd += m_libpath + ".so";

    std::system(cmd.c_str());

    m_lib   = idk::dynamiclib::loadObject(m_libpath.c_str());
    m_libpath +=  + ".so";

    m_entry = idk::dynamiclib::loadFunction(m_lib, "idk_scriptentry");
}


void
idk::RuntimeScript::_unload()
{
    idk::dynamiclib::unloadObject(m_lib);
    std::string cmd = "rm " + m_libpath;
    std::system(cmd.c_str());
}



idk::RuntimeScript::RuntimeScript( const std::string &filepath )
{
    this->_load(filepath);
}


idk::RuntimeScript::~RuntimeScript()
{
    this->_unload();
    
}


int
idk::RuntimeScript::execute( idk::EngineAPI &api )
{
    return idk::dynamiclib::call<int, idk::EngineAPI &>(m_entry, api);
}


void
idk::RuntimeScript::reload()
{
    this->_unload();
    this->_load(m_filepath);
}


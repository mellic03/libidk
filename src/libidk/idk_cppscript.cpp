#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "idk_assert.hpp"
#include "idk_cppscript.hpp"
#include "idk_dynamiclib.hpp"



static std::string
idk_genCompileCommand( const std::string &compiler,
                       const std::string &cppstd,
                       const std::string &inpath,
                       const std::string &outpath,
                       const std::string &includepath,
                       const std::string &libpath )
{
    std::string cmd =  compiler + " ";
                cmd += "-std=" + cppstd + " ";
                cmd += inpath + " ";
                cmd += "-shared -fPIC ";
                cmd += "-o " + outpath + ".so ";
                cmd += "-I" + includepath + " -L" + libpath + " ";
                cmd += "-lidk -lIDKGraphics -lIDKGameEngine ";

    return cmd;
}



void
idk::RuntimeScript::_load( const std::string &filepath )
{
    m_filepath = filepath;

    std::filesystem::path path(filepath);
    m_libpath = "IDKGE/temp/" + path.relative_path().stem().string();

    std::string cmd = idk_genCompileCommand(
        "g++",
        "c++17",
        m_filepath,
        m_libpath,
        "../include/",
        "../lib/"
    );

    std::cout << "Compiling script: \"" << cmd << "\"\n";
    int result = std::system(cmd.c_str());
    IDK_ASSERT("Error compiling script", result != 0);

    m_lib   = idk::dynamiclib::loadObject(m_libpath.c_str());
    m_entry = idk::dynamiclib::loadFunction(m_lib, "idk_scriptentry");
    m_libpath += ".so";
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


#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "idk_assert.hpp"
#include "idk_serialize.hpp"
#include "idk_cppscript.hpp"
#include "idk_dynamiclib.hpp"
#include "idk_threadpool.hpp"
#include "idk_log.hpp"


#include "idk_platform.hpp"

#ifdef IDK_UNIX
    #define DLIB_EXT ".so"
#elif defined(IDK_WINDOWS)
    #define DLIB_EXT ".dll"
#endif



namespace fs = std::filesystem;


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
                cmd += "-o " + outpath + " ";
                cmd += "-I" + includepath + " -L" + libpath + " ";

    return cmd;
}



void
idk::RuntimeScript::_load()
{
    auto dir = RuntimeScript::m_script_dir;
    auto ext = RuntimeScript::m_script_ext;
    auto *data = m_data.get();

    if (RuntimeScript::m_script_ext == ".cpp")
    {
        std::string cmd = idk_genCompileCommand(
            "g++",
            "c++20",
            data->filepath,
            data->libpath,
            "./include/",
            "./lib/"
        );

        std::cout << "Compiling script: \"" << cmd << "\" ..." << std::flush;
        int res = std::system(cmd.c_str());
        std::cout << "done!\n";

        IDK_ASSERT("Error compiling script", (res == 0));
    }

    else if (RuntimeScript::m_script_ext == DLIB_EXT)
    {
        if (fs::exists(data->libpath))
        {
            fs::remove(data->libpath);
        }

        fs::copy_file(data->filepath, data->libpath);
    }

    data->lib   = idk::dynamiclib::loadObject(data->libpath.c_str());
    data->entry = idk::dynamiclib::loadFunction(data->lib, "script");

    data->ready.store(true);
}


void
idk::RuntimeScript::_unload()
{
    auto &data = getData();

    idk::dynamiclib::unloadObject(data.lib);
    data.ready.store(false);
}



idk::RuntimeScript::RuntimeScript( const std::string &filename, bool concurrent )
{
    m_data = std::make_shared<RuntimeScript::Data>();

    auto dir = RuntimeScript::m_script_dir;
    auto ext = RuntimeScript::m_script_ext;
    auto &data = getData();

    data.filename = filename;
    data.filepath = ( fs::path(dir) / fs::path(filename + ext) ).string();
    data.libpath  = ( fs::path("IDKGE/temp/") / fs::path(filename + DLIB_EXT) ).string();

    if (concurrent)
    {
        _reload();
    }

    else
    {
        _load();
        data.ready.store(true);
    }
}


idk::RuntimeScript::~RuntimeScript()
{
    if (this->is_ready())
    {
        this->_unload();
    }
}


void
idk::RuntimeScript::setScriptDirectory( const std::string &dir )
{
    m_script_dir = fs::path(dir).string();
}


void
idk::RuntimeScript::setScriptExtension( const std::string &ext )
{
    m_script_ext = ext;
}


int
idk::RuntimeScript::execute( idk::EngineAPI &api, void *data )
{
    if (is_ready() == false)
    {
        return 0;
    }

    return idk::dynamiclib::call<int, idk::EngineAPI&, void*>(
        m_data.get()->entry, api, data
    );
}


void
idk::RuntimeScript::_reload()
{
    auto *ready = &(this->getData().ready);
    
    ready->store(false);

    idk::ThreadPool::createTask(
        [this, ready]()
        {
            this->_load();
            ready->store(true);
        }
    );
}


void
idk::RuntimeScript::reload()
{
    if (is_ready() == false)
    {
        return;
    }

    _unload();
    _reload();
}


void
idk::RuntimeScript::saveLib( const std::string &dst )
{
    auto &data = getData();

    if (fs::exists(dst))
    {
        fs::remove(dst);
        LOG_INFO() << "Deleted file which already existed: \"" << dst << "\"";
    }

    fs::copy_file(data.libpath, dst);
    LOG_INFO() << "Copied file \"" << data.libpath << "\" to \"" << dst << "\"";
}


size_t
idk::RuntimeScript::serialize( std::ofstream &stream ) const
{
    auto &data = getData();

    size_t n = 0;
    n += idk::streamwrite(stream, data.filepath);
    return n;
}


size_t
idk::RuntimeScript::deserialize( std::ifstream &stream )
{
    auto &data = getData();

    size_t n = 0;
    n += idk::streamread(stream, data.filepath);

    return n;
}
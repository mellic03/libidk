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
                cmd += "-shared -fPIC ";
                cmd += inpath + " ";
                cmd += "-o " + outpath + " ";
                cmd += "-I" + includepath + " -L" + libpath + " ";

    #ifdef IDK_DEBUG
        cmd += "-O0 -g ";
    #else
        cmd += "-Ofast ";
    #endif

    return cmd;
}



void
idk::RuntimeScript::_load()
{
    auto *data = m_data.get();
    auto ext = data->ext;

    const auto src_cache_dir = fs::path(m_script_cache_dir);
    const auto cached_path = src_cache_dir / data->filepath;
    const auto parent_path = fs::path(data->libpath).parent_path();

    if (fs::exists(parent_path) == false)
    {
        fs::create_directories(parent_path);
    }

    if (ext == ".cpp")
    {
        std::string cmd = idk_genCompileCommand(
            "g++",
            "c++23",
            cached_path,
            data->libpath,
            "./include/ " + RuntimeScript::m_args_include + " ",
            "./ " + RuntimeScript::m_args_lib + " "
        );

        std::cout << "Compiling script: \"" << cmd << "\" ..." << std::flush;
        int res = std::system(cmd.c_str());
        std::cout << "done!\n";

        std::string msg = "Error compiling script: " + cmd + "\n";
        IDK_ASSERT(msg.c_str(), (res == 0));
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
    m_filename = filename;
    _init(filename, concurrent);
}


void
idk::RuntimeScript::_init( const std::string &filename, bool concurrent )
{
    const auto src_cache_dir = fs::path(m_script_cache_dir);
    const auto bin_cache_dir = fs::path(m_dlib_cache_dir);

    if (fs::exists(src_cache_dir) == false)
    {
        fs::create_directories(src_cache_dir);
    }

    if (fs::exists(bin_cache_dir) == false)
    {
        fs::create_directories(bin_cache_dir);
    }



    m_data = std::make_shared<RuntimeScript::Data>();

    // auto dir = RuntimeScript::m_script_dir;
    // auto ext = RuntimeScript::m_script_ext;
    auto &data = getData();

    data.filename = filename;
    data.filepath = ( fs::path(filename + ".cpp") ).string();
    data.libpath  = ( bin_cache_dir / fs::path(filename + DLIB_EXT) ).string();
    data.ext      = ".cpp";

    if (cpp_cached(data.filepath) && cpp_recent(data.filepath) && dlib_cached(data.libpath))
    {
        data.filepath = ( bin_cache_dir / fs::path(filename + DLIB_EXT) ).string();
        data.ext      = DLIB_EXT;
    }

    else
    {
        make_cached(data.filepath);
    }

    auto *ready = &(this->getData().ready);
    ready->store(false);

    if (concurrent)
    {
        idk::ThreadPool::createTask(
            [this, ready]()
            {
                this->_load();
                ready->store(true);
            }
        );
    }

    else
    {
        this->_load();
        ready->store(true); 
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
idk::RuntimeScript::setCompilerInclude( const char *args )
{
    RuntimeScript::m_args_include = std::string(args);
    // m_script_dir = fs::path(dir).string();
}


void
idk::RuntimeScript::setCompilerLib( const char *args )
{
    RuntimeScript::m_args_lib = std::string(args);
    // m_script_ext = ext;
}


bool
idk::RuntimeScript::cpp_cached( const std::string &source_path )
{
    const auto src_cache_dir = fs::path(m_script_cache_dir);
    const auto cached_path = src_cache_dir / source_path;
    // std::cout << "[RuntimeScript::cpp_cached] cached_path: " << cached_path << "\n";
    return fs::exists(cached_path);
}


bool
idk::RuntimeScript::dlib_cached( const std::string &libpath )
{
    return fs::exists(libpath);
}



bool
idk::RuntimeScript::cpp_recent( const std::filesystem::path &source_path )
{
    const auto src_cache_dir = fs::path(m_script_cache_dir);
    const auto cached_path = src_cache_dir / source_path;
    
    auto t0 = fs::last_write_time(source_path);
    auto t1 = fs::last_write_time(cached_path);

    // std::cout << "\n[cpp_recent] source_path: \"" << source_path << "\"\n";
    // std::cout << "\n[cpp_recent] cached_path: \"" << cached_path << "\"\n";
    // std::cout << "[cpp_recent] t0: \"" << t0 << "\"\n";
    // std::cout << "[cpp_recent] t1: \"" << t1 << "\"\n";

    // if (t0 < t1)
    // {
    //     std::cout << "file in date!\n\n";
    // }
    // else
    // {
    //     std::cout << "file out of date!\n\n";
    // }

    return (t0 < t1);
}


void
idk::RuntimeScript::make_cached( const std::filesystem::path &source_path )
{
    const auto src_cache_dir = fs::path(m_script_cache_dir);
    const auto bin_cache_dir = fs::path(m_dlib_cache_dir);
    const auto cached_path   = src_cache_dir / source_path;
    const auto parent_path   = cached_path.parent_path();

    if (fs::exists(cached_path))
    {
        fs::remove(cached_path);
    }

    // std::cout << "\n\n";
    // idk_printvalue(src_cache_dir);
    // idk_printvalue(bin_cache_dir);
    // idk_printvalue(source_path);
    // idk_printvalue(cached_path);
    // idk_printvalue(parent_path);
    // std::cout << "\n\n";

    if (fs::exists(parent_path) == false)
    {
        fs::create_directories(parent_path);
    }

    fs::copy_file(source_path, cached_path);
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
idk::RuntimeScript::reload()
{
    if (is_ready() == false)
    {
        return;
    }

    _unload();
    _init(m_filename, true);
}


void
idk::RuntimeScript::saveLib( const std::string &dst )
{
    auto &data = getData();

    if (fs::exists(dst))
    {
        fs::remove(dst);
        // LOG_INFO() << "Deleted file which already existed: \"" << dst << "\"";
    }

    fs::copy_file(data.libpath, dst);
    // LOG_INFO() << "Copied file \"" << data.libpath << "\" to \"" << dst << "\"";
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
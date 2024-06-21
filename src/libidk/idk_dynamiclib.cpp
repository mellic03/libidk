#include "idk_dynamiclib.hpp"

#include "idk_assert.hpp"
#include "idk_platform.hpp"

#include <filesystem>
#include <iostream>

#include <SDL2/SDL_loadso.h>


#ifdef IDK_UNIX
    #define IDK_DYNAMIC_LIBRARY_FILE_EXTENSION ".so"
#elif defined(IDK_WINDOWS)
    #define IDK_DYNAMIC_LIBRARY_FILE_EXTENSION ".dll"
#endif




void *
idk::dynamiclib::loadObject( const char *filepath )
{
    std::string relpath = filepath;

    if (relpath.substr(relpath.length() - 3) == ".so")
    {
        relpath.pop_back();
        relpath.pop_back();
        relpath.pop_back();
    }

    else if (relpath.substr(relpath.length() - 4) == ".dll")
    {
        relpath.pop_back();
        relpath.pop_back();
        relpath.pop_back();
        relpath.pop_back();
    }

    std::string extension = IDK_DYNAMIC_LIBRARY_FILE_EXTENSION;
    std::string path = std::filesystem::absolute(relpath + extension).string();

    void *lib = SDL_LoadObject(path.c_str());
    if (lib == nullptr)
    {
        std::cout << SDL_GetError() << "\n";
    }

    std::string msg = "Could not load shared library from path: " + path;
    IDK_ASSERT(msg.c_str(), lib != nullptr);

    return lib;
}


void *
idk::dynamiclib::loadFunction( void *lib, const char *symbol )
{
    void *function_ptr = SDL_LoadFunction(lib, symbol);
    if (function_ptr == nullptr)
    {
        std::cout << SDL_GetError() << "\n";
    }

    std::string msg = "Could not load symbol: " + std::string(symbol);
    IDK_ASSERT(msg.c_str(), function_ptr != nullptr);

    return function_ptr;
}


void
idk::dynamiclib::unloadObject( void *lib )
{
    SDL_UnloadObject(lib);
}














namespace fs = std::filesystem;


idk::DynamicLoader::DynamicLoader( const std::string &filepath )
{
    std::string stem = fs::path(filepath).stem();

    m_realpath = filepath;
    m_temppath = "IDKGE/temp/" + stem + ".so";

    _load();
}



idk::DynamicLoader::DynamicLoader( idk::DynamicLoader &&rhs )
{
    *this = std::move(rhs);
}



idk::DynamicLoader &
idk::DynamicLoader::operator = ( idk::DynamicLoader &&rhs )
{
    if (this == &rhs)
    {
        return *this;
    }

    m_realpath    = std::move(rhs.m_realpath);
    m_temppath    = std::move(rhs.m_temppath);
    m_lib         = std::move(rhs.m_lib);
    m_functionptr = std::move(rhs.m_functionptr);
    m_data        = std::move(rhs.m_data);
    m_loaded      = std::move(rhs.m_loaded);

    rhs.m_moved   = true;
    this->m_moved = false;

    return *this;
}



idk::DynamicLoader::~DynamicLoader()
{
    if (is_moved() == false)
    {
        _unload();
    }
}



void
idk::DynamicLoader::_load()
{
    if (fs::exists(m_temppath))
    {
        fs::remove(m_temppath);
    }

    fs::copy_file(m_realpath, m_temppath);

    m_lib = idk::dynamiclib::loadObject(m_temppath.c_str());
    m_functionptr = idk::dynamiclib::loadFunction(m_lib, "getInstance");
    m_data = idk::dynamiclib::call<void *>(m_functionptr);

    m_loaded = true;
}



void
idk::DynamicLoader::_unload()
{
    void *ptr = idk::dynamiclib::loadFunction(m_lib, "deleteInstance");
    idk::dynamiclib::call<void, void *>(ptr, m_data);

    idk::dynamiclib::unloadObject(m_lib);

    if (fs::exists(m_temppath))
    {
        fs::remove(m_temppath);
    }

    m_loaded = false;
}



void
idk::DynamicLoader::reload()
{
    if (is_loaded())
    {
        _unload();
    }

    _load();
}



void *
idk::DynamicLoader::getData()
{
    return m_data;
}



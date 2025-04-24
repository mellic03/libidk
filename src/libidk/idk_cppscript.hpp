#pragma once

#include "idk_api_loader.hpp"

#include <atomic>
#include <mutex>
#include <string>
#include <fstream>
#include <memory>
#include <filesystem>


namespace idk
{
    class Threadpool;
    class EngineAPI;
    class RuntimeScript;
}


class idk::RuntimeScript
{
private:

    struct Data
    {
        std::atomic_bool ready;
        void *lib, *entry;
        std::string filename, filepath, libpath, ext;
    
        Data()
        {
            this->ready.store(false);
        }
    };

    inline static std::string m_script_cache_dir = "./IDKGE/cache/scripts/src/";
    inline static std::string m_dlib_cache_dir = "./IDKGE/cache/scripts/bin/";
    inline static std::string m_args_include = "";
    inline static std::string m_args_lib     = "";


    // inline static std::string m_script_dir = "./assets/scripts/";
    // inline static std::string m_script_ext = ".cpp";

    std::string m_filename = "";
    std::shared_ptr<Data> m_data;
    std::mutex m_mutex;

    Data& getData() const { return *(m_data.get()); }

    void  _init( const std::string &filename, bool concurrent );
    void  _load();
    void  _unload();
    void  _reload();


public:
    int id = -1;
    inline static idk::Threadpool *threadpool = nullptr;

    /**
     * @param filepath filepath relative to RuntimeScript::script_dir
     */
    RuntimeScript( const std::string &filepath, bool concurrent=true );
    ~RuntimeScript();

    // static void initThreadedLoader( idk::ThreadPool* );
    static void setScriptDirectory( const std::string &dir );
    static void setScriptExtension( const std::string &ext );

    static void setCompilerInclude( const char* );
    static void setCompilerLib( const char* );

    static bool cpp_cached( const std::string &name );
    static bool dlib_cached( const std::string &name );
    static bool cpp_recent( const std::filesystem::path &src );
    static void make_cached( const std::filesystem::path &src );


    bool        is_ready() { return m_data->ready.load(); };

    int         execute( idk::EngineAPI&, void *data = nullptr );
    void        reload();
    void        saveLib( const std::string &dst );

    const std::string &name() { return m_data->filename; };

    size_t serialize( std::ofstream &stream ) const;
    size_t deserialize( std::ifstream &stream );
};


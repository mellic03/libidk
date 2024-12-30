#pragma once

#include "idk_api_loader.hpp"

#include <atomic>
#include <mutex>
#include <string>
#include <fstream>
#include <memory>


namespace idk
{
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
        std::string filename, filepath, libpath;
    
        Data()
        {
            this->ready.store(false);
        }
    };


    inline static std::string m_script_dir = "./assets/scripts/";
    inline static std::string m_script_ext = ".cpp";

    std::shared_ptr<Data> m_data;
    std::mutex m_mutex;

    Data& getData() const { return *(m_data.get()); }
    void  _load();
    void  _unload();
    void  _reload();


public:

    int  id = -1;

    /**
     * @param filepath filepath relative to RuntimeScript::script_dir
     */
    RuntimeScript( const std::string &filepath, bool concurrent=true );
    ~RuntimeScript();

    // static void initThreadedLoader( idk::ThreadPool* );
    static void setScriptDirectory( const std::string &dir );
    static void setScriptExtension( const std::string &ext );

    bool        is_ready() { return m_data->ready.load(); };

    int         execute( idk::EngineAPI&, void *data = nullptr );
    void        reload();
    void        saveLib( const std::string &dst );

    const std::string &name() { return m_data->filename; };

    size_t serialize( std::ofstream &stream ) const;
    size_t deserialize( std::ifstream &stream );
};


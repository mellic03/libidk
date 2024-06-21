#pragma once

#include <deque>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <filesystem>
#include <chrono>


#define IDK_LOGGING


namespace idk
{
    class Logger;
    class Loggable;
    class LogStream;

    enum class LogType: uint32_t
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

};


class idk::LogStream
{
private:
    uint32_t m_flags;

    std::stringstream m_ss;

    std::string       m_type;
    std::string       m_file;
    std::string       m_func;
    int               m_line;


public:

    LogStream( uint32_t flags, idk::LogType type, const std::string &file,
               const std::string &func, int line )
    :   m_flags (flags),
        m_file  (std::filesystem::path(file).filename().string()),
        m_func  (func),
        m_line  (line)
    {
        switch (type)
        {
            default:
            case idk::LogType::INFO:  m_type = "[info] "; break;
            case idk::LogType::DEBUG: m_type = "[debug]"; break;
            case idk::LogType::WARN:  m_type = "[warn] "; break;
            case idk::LogType::ERROR: m_type = "[error]"; break;
        }

        m_ss << "[" << std::chrono::high_resolution_clock::now() << "] "
             << m_type << " ";
            //  << m_file << " "
            //  << m_func << " "
            //  << m_line << " ";
    }

    template <typename T>
    LogStream &operator << ( const T &data )
    {
        m_ss << data;
        return *this;
    }

    std::string str() const
    {
        return m_ss.str();
    }

};



class idk::Logger
{
public:
    enum Idx
    {
        IDX_FILENAME = 0,
        IDX_FILEPATH,
        IDX_LINE,
        IDX_VAR_NAME,
        IDX_VAR_VALUE,
        IDX_NUM_IDX
    };

    enum Flag
    {
        LOG_FILENAME   = 1 << IDX_FILENAME,
        LOG_FILEPATH   = 1 << IDX_FILEPATH,
        LOG_LINE       = 1 << IDX_LINE,
        LOG_VAR_NAME   = 1 << IDX_VAR_NAME,
        LOG_VAR_VALUE  = 1 << IDX_VAR_VALUE
    };


private:
    struct LogToken
    {
        std::chrono::high_resolution_clock::time_point timestamp;
        LogType     type;
        std::string data[IDX_NUM_IDX];
    };

    inline static uint32_t               m_flags;
    inline static std::vector<LogStream> m_history;
    inline static size_t                 m_temp_idx = 0;


public:

    static void init( uint32_t flags = 0 )
    {
        m_flags = flags;
    };


    static idk::LogStream &log( idk::LogType type, const std::string &file,
                                const std::string &func, int line )
    {
        m_history.push_back(idk::LogStream(m_flags, type, file, func, line));
        return m_history.back();
    };

    static void print()
    {
        if (m_temp_idx == m_history.size())
        {
            return;
        }

        for (size_t i=m_temp_idx; i<m_history.size(); i++)
        {
            std::cout << m_history[i].str() << "\n";
        }

        m_temp_idx = m_history.size();
    }

    static void write()
    {
        std::stringstream ss;
        ss << std::chrono::high_resolution_clock::now();
        std::string filepath = "log/" + ss.str() + ".txt";

        std::ofstream stream(filepath);

        for (idk::LogStream &l: m_history)
        {
            stream << l.str() << "\n";
        }

        stream.close();
    }

};


#ifdef IDK_LOGGING
    #define LOG_INFO()  idk::Logger::log(idk::LogType::INFO,  __FILE__, __PRETTY_FUNCTION__, __LINE__)
    #define LOG_DEBUG() idk::Logger::log(idk::LogType::DEBUG, __FILE__, __PRETTY_FUNCTION__, __LINE__)
    #define LOG_WARN()  idk::Logger::log(idk::LogType::WARN,  __FILE__, __PRETTY_FUNCTION__, __LINE__)
    #define LOG_ERROR() idk::Logger::log(idk::LogType::ERROR, __FILE__, __PRETTY_FUNCTION__, __LINE__)

#else
    #define LOG_INFO(lbl)
    #define LOG_DEBUG(lbl)
    #define LOG_WARN(lbl)
    #define LOG_ERROR(lbl)
#endif



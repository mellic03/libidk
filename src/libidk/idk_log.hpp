#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <format>
#include "idk_assert.hpp"


#define LOG_ADVGING


namespace idk
{
    class Logger;

    struct log_flag {
        enum internal_type: uint32_t {
            PRINT_LAZY = 1 << 1,
            DETAIL = 1 << 2,
            INFO   = 1 << 3,
            DEBUG  = 1 << 4,
            WARN   = 1 << 5,
            ERROR  = 1 << 6,
            FATAL  = 1 << 7,

            RENDER = 1 << 8,
            AUDIO  = 1 << 9,
            IO     = 1 << 10,
            API    = 1 << 11,

            EVERYTHING = 1 << 12,

            DEFAULT = PRINT_LAZY|INFO|WARN|ERROR|FATAL
        };
    };
};



class idk::Logger
{
public:

private:
    struct Token
    {
        const char *color;
        std::string time, ltype, title, msg;
    };

    inline static std::vector<Token> m_backbuffer;
    inline static std::vector<Token> m_frontbuffer;
    inline static std::string m_filepath = "";
    
public:
    inline static uint32_t flags = log_flag::DEFAULT;

    static void init();
    static void update();
    static void log( uint32_t type, const std::string &title, const std::string &msg );
    static void log( uint32_t type, const std::string &title );
    static void log( const std::string &title, const std::string &msg );
    static void log( const std::string &title );
    static void print();
    static void writeFile();

};


#ifdef LOG_ADVGING
    #define LOG_ADV(log__flags, ...) idk::Logger::log(log__flags, __PRETTY_FUNCTION__, std::format(__VA_ARGS__, ""))
    #define LOG_DETAIL(...) idk::Logger::log(idk::log_flag::DETAIL,  __PRETTY_FUNCTION__, std::format(__VA_ARGS__))
    #define LOG_INFO(...) idk::Logger::log(idk::log_flag::INFO,  __PRETTY_FUNCTION__, std::format(__VA_ARGS__))
    #define LOG_DEBUG(...) idk::Logger::log(idk::log_flag::DEBUG,  __PRETTY_FUNCTION__, std::format(__VA_ARGS__))
    #define LOG_WARN(...) idk::Logger::log(idk::log_flag::WARN,  __PRETTY_FUNCTION__, std::format(__VA_ARGS__))
    #define LOG_ERROR(...) idk::Logger::log(idk::log_flag::ERROR,  __PRETTY_FUNCTION__, std::format(__VA_ARGS__))
    #define LOG_FATAL(...) idk::Logger::log(idk::log_flag::FATAL,  __PRETTY_FUNCTION__, std::format(__VA_ARGS__))
    #define LOG_ASSERT(__ass__, ...) if (!(__ass__)) { idk::Logger::log(idk::log_flag::FATAL,  __PRETTY_FUNCTION__, std::format(__VA_ARGS__)); }\


#else
    #define LOG_ADV(log__flags, ...)
    #define LOG_DETAIL(...)
    #define LOG_INFO(...)
    #define LOG_DEBUG(...)
    #define LOG_WARN(...)
    #define LOG_ERROR(...)
    #define LOG_FATAL(...)
    #define LOG_ASSERT(__ass__, ...)
#endif



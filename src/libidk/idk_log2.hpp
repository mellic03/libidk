#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <format>


#define IDK_LOGGING


namespace idk
{
    class Logger2;

    enum class LogType2: uint32_t
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

};



class idk::Logger2
{
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
    static void init();
    static void update();
    static void log( idk::LogType2 type, const std::string &title, const std::string &msg );
    static void print();
    static void writeFile();

};


#ifdef IDK_LOGGING
    #define LOG_INFO_1(log__title) idk::Logger2::log(idk::LogType2::INFO,  log__title, "")
    #define LOG_DEBUG_1(log__title) idk::Logger2::log(idk::LogType2::DEBUG, log__title, "")
    #define LOG_WARN_1(log__title) idk::Logger2::log(idk::LogType2::WARN,  log__title, "")
    #define LOG_ERROR_1(log__title) idk::Logger2::log(idk::LogType2::ERROR, log__title, "")

    #define LOG_INFO_2(log__title, log__msg) idk::Logger2::log(idk::LogType2::INFO,  log__title, log__msg)
    #define LOG_DEBUG_2(log__title, log__msg) idk::Logger2::log(idk::LogType2::DEBUG, log__title, log__msg)
    #define LOG_WARN_2(log__title, log__msg) idk::Logger2::log(idk::LogType2::WARN,  log__title, log__msg)
    #define LOG_ERROR_2(log__title, log__msg) idk::Logger2::log(idk::LogType2::ERROR, log__title, log__msg)

    #define GET_MACRO(_1, _2, NAME, ...) NAME
    #define LOG_INFO(...) GET_MACRO(__VA_ARGS__, LOG_INFO_2, LOG_INFO_1)(__VA_ARGS__)
    #define LOG_DEBUG(...) GET_MACRO(__VA_ARGS__, LOG_DEBUG_2, LOG_DEBUG_1)(__VA_ARGS__)
    #define LOG_WARN(...) GET_MACRO(__VA_ARGS__, LOG_WARN_2, LOG_WARN_1)(__VA_ARGS__)
    #define LOG_ERROR(...) GET_MACRO(__VA_ARGS__, LOG_ERROR_2, LOG_ERROR_1)(__VA_ARGS__)

#else
    #define LOG_INFO(log__title, log__msg)
    #define LOG_DEBUG(log__title, log__msg)
    #define LOG_WARN(log__title, log__msg)
    #define LOG_ERROR(log__title, log__msg)
#endif



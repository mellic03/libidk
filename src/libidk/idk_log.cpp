#include "idk_ansi.hpp"
#include "idk_assert.hpp"
#include "idk_log.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <print>
#include <chrono>



void
idk::Logger::init()
{
    std::string time = std::format("{:%Y-%m-%d %H:%M:%OS}", std::chrono::high_resolution_clock::now());
    m_filepath = std::format("./log/{}.txt", time);

    std::ofstream stream(m_filepath);

    if (stream.good())
    {
        std::print("[{}] [info]  [idk:::Logger::int] Opened file \"{}\"", time, m_filepath);
    }

    LOG_INFO("");

    stream << "Initialized at " << time << "\n";
    stream.close();
}


void
idk::Logger::update()
{
    static uint32_t count = 0;
    Logger::print();

    if (count >= 1024 && m_backbuffer.size() > 0)
    {
        Logger::writeFile();
        m_backbuffer.clear();
        count = 0;
    }
    count += 1;
}


void
idk::Logger::log( uint32_t tp, const std::string &title, const std::string &msg )
{
    auto color = ANSI::RESET;
    std::string type;

    switch (tp)
    {
        default:
        case log_flag::DETAIL: type = "[verbose] "; color = ANSI::Reg::GRN;  break;
        case log_flag::INFO:   type = "[info]    "; color = ANSI::Reg::GRN;  break;
        case log_flag::DEBUG:  type = "[debug]   "; color = ANSI::Reg::BLU;  break;
        case log_flag::WARN:   type = "[warn]    "; color = ANSI::Bd::YEL;   break;
        case log_flag::ERROR:  type = "[error]   "; color = ANSI::BdHi::RED; break;
        case log_flag::FATAL:  type = "[fatal]   "; color = ANSI::BdHi::RED; break;
    }

    if ((tp & Logger::flags) != tp)
    {
        return;
    }

    Token token = {
        color,
        std::format("[{:%Y/%m/%d-%Hh%Mm%OSs}] ", std::chrono::high_resolution_clock::now()),
        type,
        "[" + title + "] ",
        msg
    };

    m_frontbuffer.push_back(token);

    if (tp & log_flag::FATAL)
    {
        Logger::print();
        Logger::writeFile();
        IDK_ASSERT("Fatal error", false);
    }

    // if ((Logger::flags & log_flag::PRINT_LAZY) == false)
    // {
    //     Logger::print();
    //     std::cout << std::flush;
    // }
}

void
idk::Logger::log( uint32_t type, const std::string &title )
{
    log(type, title, "");
}

void
idk::Logger::log( const std::string &title, const std::string &msg )
{
    log(Logger::flags, title, msg);
}

void
idk::Logger::log( const std::string &title )
{
    log(Logger::flags, title, "");
}



void
idk::Logger::print()
{
    static std::string output;

    for (Token &t: m_frontbuffer)
    {
        output = t.time
               + t.color + t.ltype + ANSI::RESET
               + t.title
               + t.msg
               + "\n";

        std::cout << output;
        m_backbuffer.push_back(t);
    }

    m_frontbuffer.clear();
}


void
idk::Logger::writeFile()
{
    static std::string output;
    std::ofstream stream(m_filepath, std::ios::app);

    for (Token &t: m_backbuffer)
    {
        output = t.time + t.ltype + t.title + t.msg + "\n";
        stream << output;
    }

    stream.close();
}


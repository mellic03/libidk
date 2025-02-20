#include "idk_log2.hpp"
#include "idk_ansi.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <print>
#include <chrono>

// static constexpr auto RESET  = "\033[0m";
// static constexpr auto BLACK  = "\033[30m";
// static constexpr auto RED    = "\033[91m";
// static constexpr auto GREEN  = "\033[92m";
// static constexpr auto YELLOW = "\033[93m";
// static constexpr auto BLUE   = "\033[94m";



void
idk::Logger2::init()
{
    std::string time = std::format("{:%Y-%m-%d %H:%M:%OS}", std::chrono::high_resolution_clock::now());
    m_filepath = std::format("./log/{}.txt", time);

    std::ofstream stream(m_filepath);

    if (stream.good())
    {
        std::print("[{}] [info]  [idk:::Logger2::int] Opened file \"{}\"", time, m_filepath);
    }

    // LOG_INFO("idk::Logger2::init", "initialized");

    stream << "Initialized at " << time << "\n";
    stream.close();
}


void
idk::Logger2::update()
{
    static uint32_t count = 0;

    Logger2::print();

    if (count >= 1024 && m_backbuffer.size() > 0)
    {
        Logger2::writeFile();
        m_backbuffer.clear();
        count = 0;
    }
    count += 1;
}


void
idk::Logger2::log( idk::LogType2 tp, const std::string &title, const std::string &msg )
{
    auto color = ANSI::RESET;
    std::string type;

    switch (tp)
    {
        default:
        case idk::LogType2::INFO:  type = "[info]  "; color = ANSI::Reg::GRN;  break;
        case idk::LogType2::DEBUG: type = "[debug] "; color = ANSI::Reg::BLU;  break;
        case idk::LogType2::WARN:  type = "[warn]  "; color = ANSI::Bd::YEL;   break;
        case idk::LogType2::ERROR: type = "[error] "; color = ANSI::BdHi::RED; break;
    }

    Token token = {
        color,
        std::format("[{:%Y/%m/%d-%Hh%Mm%OSs}] ", std::chrono::high_resolution_clock::now()),
        type,
        "[" + title + "] ",
        msg
    };

    m_frontbuffer.push_back(token);
}


void
idk::Logger2::print()
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
idk::Logger2::writeFile()
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


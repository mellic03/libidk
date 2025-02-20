// #include "idk_log.hpp"


// static constexpr auto RESET  = "\033[0m";
// static constexpr auto BLACK  = "\033[30m";
// static constexpr auto RED    = "\033[91m";
// static constexpr auto GREEN  = "\033[92m";
// static constexpr auto YELLOW = "\033[93m";
// static constexpr auto BLUE   = "\033[94m";


// idk::LogStream::LogStream( uint32_t flags, idk::LogType type, const std::string &file,
//                            const std::string &func, int line )
// :   m_flags (flags),
//     m_file  (std::filesystem::path(file).filename().string()),
//     m_func  (func),
//     m_line  (line)
// {
//     auto color = RESET;

//     switch (type)
//     {
//         default:
//         case idk::LogType::INFO:  m_type = "[info]  "; color = GREEN;  break;
//         case idk::LogType::DEBUG: m_type = "[debug] "; color = BLUE;   break;
//         case idk::LogType::WARN:  m_type = "[warn]  "; color = YELLOW; break;
//         case idk::LogType::ERROR: m_type = "[error] "; color = RED;    break;
//     }

//     m_ss << "[" << std::chrono::high_resolution_clock::now() << "] "
//          << color << m_type << RESET;

//     //  << m_file << " "
//     //  << m_func << " "
//     //  << m_line << " ";
// }

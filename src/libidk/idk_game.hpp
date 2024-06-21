#pragma once

#include "idk_export.hpp"
#include <string>


namespace idk { class Game; class GameHandle; };
namespace idk { class EngineAPI; };


class IDK_VISIBLE idk::Game
{
private:
    std::string m_name;

public:
    Game( const std::string &name ): m_name(name) {  };
    const std::string &getName() { return m_name; };

    virtual void registerModules ( idk::EngineAPI& ) = 0;
    virtual void setup           ( idk::EngineAPI& ) = 0;
    virtual void mainloop        ( idk::EngineAPI& ) = 0;
    virtual void shutdown        (                 ) = 0;

};

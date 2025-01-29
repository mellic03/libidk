#pragma once

#include "idk_export.hpp"
#include <vector>
#include <string>

namespace idk
{ 
    class EngineAPI;
    class Game;
}


class IDK_VISIBLE idk::Game
{
public:
    virtual std::string getName() = 0;

    virtual void setup           ( idk::EngineAPI& ) = 0;
    virtual void mainloop        ( idk::EngineAPI& ) = 0;
    virtual void shutdown        (                 ) = 0;

};

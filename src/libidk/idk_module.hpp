#pragma once

#include "idk_api_loader.hpp"

#include <typeindex>
#include <vector>
#include <string>


namespace idk
{
    class EngineAPI;
    class ECS;
}

namespace idk
{
    class Module;
}


class idk::Module
{
private:
    std::string                         m_name;

public:
    virtual                             ~Module() = default;
    
    constexpr const std::string &       name()   const { return m_name;   };

    virtual void                        init( idk::EngineAPI& ) = 0;
    virtual void                        deinit() = 0;

    virtual void                        stage_A( idk::EngineAPI& ) = 0;
    virtual void                        stage_B( idk::EngineAPI& ) = 0;
    virtual void                        stage_C( idk::EngineAPI& ) = 0;

};



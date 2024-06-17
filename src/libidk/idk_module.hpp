#pragma once

#include "idk_api_loader.hpp"

#include <typeindex>
#include <vector>
#include <string>


namespace idk { class Engine; class EngineAPI; };

namespace idk
{
    class Module;
};


class idk::Module
{
private:
    friend class idk::Engine;
    std::string                         m_name;

public:
    virtual                             ~Module() = default;
    
    constexpr const std::string &       name()   const { return m_name;   };

    virtual void                        init( idk::EngineAPI & ) = 0;
    virtual void                        deinit() {  };

    virtual void                        stage_A( idk::EngineAPI & ) = 0;
    virtual void                        stage_B( idk::EngineAPI & ) = 0;
    virtual void                        stage_C( idk::EngineAPI & ) = 0;

};



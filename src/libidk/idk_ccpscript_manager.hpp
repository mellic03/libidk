#pragma once
#include "idk_cppscript.hpp"
#include "idk_wallocator2.hpp"
#include <vector>
#include <filesystem>

namespace idk
{
    class ScriptManager;
}


class idk::ScriptManager
{
private:
    idk::WAllocator2<idk::RuntimeScript*> m_scripts;

public:

    ScriptManager();


};




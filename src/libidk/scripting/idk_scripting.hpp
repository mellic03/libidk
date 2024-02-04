#pragma once

#include "luaaa.hpp"
#include <vector>


namespace idk
{
    class LuaManager;
    class LuaAPI;
};



class idk::LuaManager
{
private:
    static inline std::vector<idk::LuaAPI *> lua_modules;

public:
    static void       pushModule( idk::LuaAPI *api ) { lua_modules.push_back(api); };
    static lua_State *newState();

};



class idk::LuaAPI
{
public:
    virtual        ~LuaAPI() = default;
                    LuaAPI() { LuaManager::pushModule(this);  }; 

    virtual void    exposeToLua( lua_State *L ) = 0;
};



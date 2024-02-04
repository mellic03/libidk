#include "idk_scripting.hpp"




lua_State *
idk::LuaManager::newState()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    for (auto *mod: lua_modules)
    {
        mod->exposeToLua(L);
    }

    return L;
}

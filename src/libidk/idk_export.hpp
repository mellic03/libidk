#pragma once


#define IDK_VISIBLE  __attribute__ ((visibility("default")))
#define IDK_VISIBILITY_HIDDEN   __attribute__ ((visibility("hidden")))
#define IDK_VISIBILITY_INTERNAL __attribute__ ((visibility("internal")))


// Export macro
// ---------------------------------------------------------------------------------------------
#define IDK_EXPORT_API( declaration ) extern "C" { IDK_VISIBLE declaration }

#define IDK_EXPORT_MODULE(module_type) \
\
extern "C" \
{ \
    static module_type *mod = nullptr; \
\
    IDK_VISIBLE \
    idk::Module *getInstance() \
    { \
        if (mod == nullptr) mod = new module_type(); \
        return dynamic_cast<idk::Module *>(mod); \
    } \
\
    IDK_VISIBLE \
    void freeInstance( module_type *other ) \
    { \
        mod->deinit(); \
        delete mod; \
        mod = nullptr; \
    } \
} \





#define IDK_EXPORT_GAME(game_type) \
\
extern "C" \
{ \
    static game_type *game = nullptr; \
\
    IDK_VISIBLE \
    idk::Game *getInstance() \
    { \
        if (game == nullptr) game = new game_type(); \
        return dynamic_cast<idk::Game *>(game); \
    } \
\
    IDK_VISIBLE \
    void freeInstance( game_type *other ) \
    { \
        game->shutdown(); \
        delete game; \
        game = nullptr; \
    } \
} \

// ---------------------------------------------------------------------------------------------

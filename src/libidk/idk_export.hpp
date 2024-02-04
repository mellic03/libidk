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
    IDK_VISIBLE \
    idk::Module *getInstance() \
    { \
        static module_type *mod = nullptr; \
        if (mod == nullptr) mod = new module_type(); \
        return dynamic_cast<idk::Module *>(mod); \
    } \
\
    IDK_VISIBLE \
    void deleteInstance( void *instance ) \
    { \
        module_type *mod = reinterpret_cast<module_type *>(instance); \
        mod->deinit(); \
        delete mod; \
    } \
} \
// ---------------------------------------------------------------------------------------------

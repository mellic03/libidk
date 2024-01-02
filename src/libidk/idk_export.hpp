#pragma once


#define IDK_VISIBLE  __attribute__ ((visibility("default")))
#define IDK_VISIBILITY_HIDDEN   __attribute__ ((visibility("hidden")))
#define IDK_VISIBILITY_INTERNAL __attribute__ ((visibility("internal")))


// Export macro
// ---------------------------------------------------------------------------------------------
#define IDK_EXPORT_API( declaration ) extern "C" { IDK_VISIBLE declaration }
// ---------------------------------------------------------------------------------------------

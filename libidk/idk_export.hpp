#pragma once

// Export macro
// ---------------------------------------------------------------------------------------------
#define IDK_VISIBLE __attribute__ ((visibility("default")))

#define IDK_EXPORT_API( declaration ) extern "C" { IDK_VISIBLE declaration }
// ---------------------------------------------------------------------------------------------

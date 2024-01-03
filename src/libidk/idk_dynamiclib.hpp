#pragma once


namespace idk::dynamiclib
{
    void *loadObject( const char *filepath );
    void *loadFunction( void *lib, const char *symbol );
    void  unloadObject( void *lib );
};

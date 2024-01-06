#pragma once

#include <cstddef>
#include <vector>


namespace idk
{
    struct CSFile;
    struct SceneFile;
};


namespace idk::Scene
{
    SceneFile   loadFile( const char * );
    void        saveFile( const SceneFile &, const char * );
};


struct idk::CSFile
{
    void  *data;
    size_t nbytes;
};


struct idk::SceneFile
{
    std::vector<idk::CSFile> CSFiles;
};
#pragma once

#include <cstdint>
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
    uint32_t  cs_id;
    void     *data;
    uint32_t  nbytes;
};


// struct idk::CSFile
// {
//     int32_t  obj_id;
//     uint32_t cs_id;
//     std::vector<uint32_t> data;
// };



struct idk::SceneFile
{
    std::vector<idk::CSFile> CSFiles;
};
#include <fstream>
#include <memory>

#include "idk_idkvi_file.hpp"


static void
idkvi_saveMaterial( std::ofstream &stream, idk::idkvi_material &material )
{
    stream.write(reinterpret_cast<const char *>(&material.bitmask), sizeof(uint32_t));

    for (int i=0; i<4; i++)
    {
        if (material.bitmask & i)
        {
            std::string &path = material.textures[i];
            uint32_t length = path.length();
            stream.write(reinterpret_cast<const char *>(&length), sizeof(uint32_t));
            stream.write(reinterpret_cast<const char *>(path.c_str()), sizeof(char) * length);
        }
    }
}


static void
idkvi_loadMaterial( std::ifstream &stream, idk::idkvi_material &material )
{
    stream.read(reinterpret_cast<char *>(&material.bitmask), sizeof(uint32_t));

    for (int i=0; i<4; i++)
    {
        if (material.bitmask & i)
        {
            uint32_t length;
            stream.read(reinterpret_cast<char *>(&length), sizeof(uint32_t));

            std::string path;
            path.resize(length);
            stream.read(reinterpret_cast<char *>(path.data()), sizeof(char)*length);
        }
    }
}


idk::idkvi_file
idk::idkvi_load( const char *filepath )
{
    std::ifstream stream(filepath);
    idkvi_file file;

    uint32_t num_vertices, num_indices, num_materials, num_meshes;
    stream.read(reinterpret_cast<char *>(&file.vertexformat),  sizeof(uint32_t));
    stream.read(reinterpret_cast<char *>(&num_vertices),       sizeof(uint32_t));
    stream.read(reinterpret_cast<char *>(&num_indices),        sizeof(uint32_t));
    stream.read(reinterpret_cast<char *>(&num_materials),      sizeof(uint32_t));
    stream.read(reinterpret_cast<char *>(&num_meshes),         sizeof(uint32_t));

    file.vertices.resize(num_vertices);
    file.indices.resize(num_indices);
    file.materials.resize(num_materials);
    file.meshes.resize(num_meshes);

    stream.read(reinterpret_cast<char *>(file.vertices.data()),  file.vertices.nbytes());
    stream.read(reinterpret_cast<char *>(file.indices.data()),   file.indices.nbytes());
    stream.read(reinterpret_cast<char *>(file.meshes.data()),    file.meshes.nbytes());

    for (uint32_t i=0; i<num_materials; i++)
    {
        idkvi_loadMaterial(stream, file.materials[i]);
    }

    stream.close();

    return file;
}


void
idk::idkvi_save( idkvi_file &file, const char *filepath )
{
    std::ofstream stream(filepath);

    uint32_t num_vertices  = file.vertices.size();
    uint32_t num_indices   = file.indices.size();
    uint32_t num_materials = file.materials.size();
    uint32_t num_meshes    = file.meshes.size();

    stream.write(reinterpret_cast<const char *>(&file.vertexformat), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char *>(&num_vertices),      sizeof(uint32_t));
    stream.write(reinterpret_cast<const char *>(&num_indices),       sizeof(uint32_t));
    stream.write(reinterpret_cast<const char *>(&num_materials),     sizeof(uint32_t));
    stream.write(reinterpret_cast<const char *>(&num_meshes),        sizeof(uint32_t));

    stream.write(reinterpret_cast<const char *>(file.vertices.data()),  file.vertices.nbytes());
    stream.write(reinterpret_cast<const char *>(file.indices.data()),   file.indices.nbytes());
    stream.write(reinterpret_cast<const char *>(file.meshes.data()),    file.meshes.nbytes());

    for (uint32_t i=0; i<num_materials; i++)
    {
        idkvi_saveMaterial(stream, file.materials[i]);
    }

    stream.close();
}


#include "idk_api_loader.hpp"
#include <vector>
#include <memory>



idk::APILoader::APILoader( const char *filepath )
{
    m_lib = idk::dynamiclib::loadObject(filepath);
}



#pragma once

#ifndef GLM_ENABLE_EXPERIMENTAL
    #define GLM_ENABLE_EXPERIMENTAL
#endif

#include "./idk_glm.hpp"
#include <vector>

namespace idk::IK
{
    void FABRIK( std::vector<glm::vec3>&, const std::vector<float>&,
                 float total_dist, int iterations = 1 );
};


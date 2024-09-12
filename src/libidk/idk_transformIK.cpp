#include "idk_transformIK.hpp"


void
idk::IK::FABRIK( std::vector<glm::vec3> &positions,
                 const std::vector<float> &distances,
                 float tdist,
                 int iterations )
{
    glm::vec3 root_pos = positions[0];
    glm::vec3 end_pos  = positions.back();
    glm::vec3 dir;

    if (glm::distance2(root_pos, end_pos) > tdist*tdist)
    {
        dir = glm::normalize(root_pos - end_pos);
        end_pos = root_pos + 0.95f*tdist*dir;
    }


    for (int j=0; j<iterations; j++)
    {
        // Backward pass
        // -----------------------------------------------------
        // for (int i=positions.size()-2; i>=0; i--)
        for (int i=positions.size()-2; i>0; i--)
        {
            glm::vec3 &left  = positions[i];
            glm::vec3 &right = positions[i+1];
        
            dir  = glm::normalize(left - right);
            left = right + distances[i]*dir;
        }
        // -----------------------------------------------------

        // Forward pass
        // -----------------------------------------------------
        for (int i=0; i<positions.size()-1; i++)
        {
            glm::vec3 &left  = positions[i];
            glm::vec3 &right = positions[i+1];

            dir  = glm::normalize(right - left);
            right = left + distances[i]*dir;
        }
        // -----------------------------------------------------
    }
}


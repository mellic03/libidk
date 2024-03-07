#pragma once

#include "idk_glm.hpp"


namespace idk::geometry
{

    float distPlanePoint( const glm::vec3 &plane, const glm::vec3 &N, const glm::vec3 &point );

    /** Return the signed distance between a plane and sphere.
     * 
    */
    float distPlaneSphere( const glm::vec3 &plane, const glm::vec3 &N, const glm::vec3 &sphere, float r );


    struct CameraFrustum
    {
        glm::vec3 positions[6];
        glm::vec3 directions[6];
    };


    CameraFrustum createCameraFrustum( float near, float far, float vfov, float aspect,
                                       const glm::vec3 &position,
                                       const glm::vec3 &front,
                                       const glm::vec3 &up,
                                       const glm::vec3 &right );

    bool inFrustum( const geometry::CameraFrustum &frustum, const glm::mat4 &T, float radius );

};

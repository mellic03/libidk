#pragma once

#include "idk_glm.hpp"


namespace idk::geometry
{
    struct AABB
    {
        glm::vec3 center;
        glm::vec3 extents;
    };

    struct Triangle
    {
        glm::vec3 v0, v1, v2;
    };


    bool AABB_AABB_Intersects( const AABB &A, const AABB &B );

    bool pointInTriangle( const glm::vec3 &point, const Triangle &tri );

    bool rayAABBIntersection( const glm::vec3 &origin, const glm::vec3 &dir,
                              const glm::vec3 &rect, const glm::vec3 &bounds,
                              glm::vec3 *res = nullptr, glm::vec3 *N = nullptr );

    bool raySphereIntersects( const glm::vec3 &ray_origin, const glm::vec3 &ray_dir,
                              const glm::vec3 &sphere_origin, float sphere_radius,
                              glm::vec3 *hit = nullptr, glm::vec3 *N = nullptr );


    float distPlanePoint( const glm::vec3 &plane, const glm::vec3 &N, const glm::vec3 &point );

    /** Return the signed distance between a plane and sphere.
     * 
    */
    float distPlaneSphere( const glm::vec3 &plane, const glm::vec3 &N, const glm::vec3 &sphere, float r );

    bool pointInRect( const glm::vec2 &p, const glm::vec2 &tl, const glm::vec2 &extents );
    bool pointInRect( float px, float py, float x, float y, float w, float h );
    bool pointInRectCentered( float px, float py, float x, float y, float w, float h );


    glm::vec3 line_point_NearestPoint( const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &p );
    glm::vec3 line_rect_NearestPoint( const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &p );


    struct SphereRectResponse
    {
        glm::vec3 s_pos;
        float     s_rad;
        glm::vec3 i_pos;
        glm::vec3 dir;
    };

    bool sphereRectIntersection( glm::vec3 s_pos, float s_radius, const glm::mat4 &rect,
                                 glm::vec3 &res );

    bool capsuleRectIntersection( const glm::vec3 &c_pos, float c_bot, float c_top, float c_rad,
                                  const glm::mat4 &rect, glm::vec3 &res );


    bool capsuleTriangleIntersection( const glm::vec3 &c_pos, float c_bot, float c_top, float c_rad,
                                      const Triangle &tri, glm::vec3 &res );


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

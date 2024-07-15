#include "idk_geometry.hpp"

#include "idk_assert.hpp"
#include "idk_log.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

bool
idk::geometry::AABB_AABB_Intersects( const AABB &A, const AABB &B )
{
    glm::vec3 Amin = A.center - (A.extents / 2.0f);
    glm::vec3 Amax = A.center + (A.extents / 2.0f);

    glm::vec3 Bmin = B.center - (B.extents / 2.0f);
    glm::vec3 Bmax = B.center + (B.extents / 2.0f);

    // return (Amin <= Bmax) && (Amax >= Bmin); 

    bool x_axis = (Amin.x <= Bmax.x) && (Amax.x >= Bmin.x);
    bool y_axis = (Amin.y <= Bmax.y) && (Amax.y >= Bmin.y);
    bool z_axis = (Amin.z <= Bmax.z) && (Amax.z >= Bmin.z);

    return x_axis && y_axis && z_axis;
}



bool
idk::geometry::rayAABBIntersection( const glm::vec3 &origin, const glm::vec3 &dir,
                                    const glm::vec3 &rect, const glm::vec3 &bounds,
                                    glm::vec3 *hit, glm::vec3 *N )
{
    // r.dir is unit direction vector of ray
    glm::vec3 inv_dir = 1.0f / dir;

    // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
    // r.org is origin of ray
    float t1 = ((rect.x - bounds.x) - origin.x) * inv_dir.x;
    float t2 = ((rect.x + bounds.x) - origin.x) * inv_dir.x;
    float t3 = ((rect.y - bounds.y) - origin.y) * inv_dir.y;
    float t4 = ((rect.y + bounds.y) - origin.y) * inv_dir.y;
    float t5 = ((rect.z - bounds.z) - origin.z) * inv_dir.z;
    float t6 = ((rect.z + bounds.z) - origin.z) * inv_dir.z;

    float tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
    float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0)
    {
        return false;
    }

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        return false;
    }

    if (hit)
    {
        (*hit) = origin + tmin*dir;

        if (N)
        {
            glm::vec3 n = *hit - rect;

            float nx = fabs(n.x) / fabs(bounds.x);
            float ny = fabs(n.y) / fabs(bounds.y);
            float nz = fabs(n.z) / fabs(bounds.z);

            if (nx > ny && nx > nz)
            {
                *N = glm::normalize(glm::vec3(n.x, 0.0f, 0.0f));
            }

            if (ny > nx && ny > nz)
            {
                *N = glm::normalize(glm::vec3(0.0f, n.y, 0.0f));
            }

            if (nz > nx && nz > ny)
            {
                *N = glm::normalize(glm::vec3(0.0f, 0.0f, n.z));
            }

            return true;
        }
    }

    return true;
}



bool
idk::geometry::raySphereIntersects( const glm::vec3 &ray_origin, const glm::vec3 &ray_dir,
                                    const glm::vec3 &sphere_origin, float sphere_radius,
                                    glm::vec3 *hit, glm::vec3 *N )
{
    glm::vec3 L = sphere_origin - ray_origin;

    float l   = length(L);
    float r   = sphere_radius;
    float tc  = dot(ray_dir, L);
    float d   = sqrt(l*l - tc*tc);
    float t1c = sqrt(r*r - d*d);

    if (d >= r)
    {
        return false;
    }

    float t1 = tc - t1c;
    float t2 = tc + t1c;

    if (hit)
    {
        if (t1 < 0.0f)
        {
            *hit = ray_origin + t2*ray_dir;
        }

        else
        {
            *hit = ray_origin + t1*ray_dir;
        }

        if (N)
        {
            *N = glm::normalize(*hit - sphere_origin);
        }
    }

    return true;

}



float
idk::geometry::distPlanePoint( const glm::vec3 &plane, const glm::vec3 &N, const glm::vec3 &point )
{
    glm::vec3 PS  = (point - plane);
    float     A   = length(PS);
    glm::vec3 dir = PS / A;

    float cosTheta   = glm::dot(N, dir);
    float theta      = glm::acos(glm::abs(cosTheta));
    float alpha      = (glm::pi<float>() / 2.0f) - theta;
    float dist       = A*glm::sin(alpha);
    float distSigned = glm::sign(cosTheta) * dist;

    return distSigned;
}


float
idk::geometry::distPlaneSphere( const glm::vec3 &plane, const glm::vec3 &N, const glm::vec3 &sphere, float r )
{
    float distCenter = distPlanePoint(plane, N, sphere);
    return distCenter - glm::sign(distCenter)*r;
}


bool
idk::geometry::pointInRect( float px, float py, float x, float y, float w, float h )
{
    return (x <= px && px <= x+w) && (y <= py && py <= y+h);
}


bool
idk::geometry::pointInRectCentered( float px, float py, float x, float y, float w, float h )
{
    return pointInRect(px, py, x-w/2, y-h/2, w, h);
}



glm::vec3 nearestPointOnLineSegment(const glm::vec3& A, const glm::vec3& B, const glm::vec3& P)
{
    // Vector from A to B
    glm::vec3 AB = B - A;
    
    // Vector from A to P
    glm::vec3 AP = P - A;
    
    // Projection factor t of P onto the line AB (parametric position on the segment)
    float AB_dot_AB = glm::dot(AB, AB);
    float AB_dot_AP = glm::dot(AB, AP);
    float t = AB_dot_AP / AB_dot_AB;
    
    // Clamp t to the range [0, 1] to ensure the nearest point is within the segment
    t = glm::clamp(t, 0.0f, 1.0f);
    
    // Calculate the nearest point using the clamped t value
    glm::vec3 nearestPoint = A + t * AB;
    
    return nearestPoint;
}


glm::vec3
idk::geometry::line_point_NearestPoint( const glm::vec3 &A, const glm::vec3 &B,
                                        const glm::vec3 &p )
{
    // glm::vec3 AB    = glm::normalize(B - A);
    // glm::vec3 Ap    = glm::normalize(p - A);
    // glm::vec3 ortho = glm::cross(Ap, AB);

    // glm::vec3 O = A; // Origin of plane
    // glm::vec3 N = glm::cross(AB, ortho); // Normal of plane

    // float dist = idk::geometry::distPlanePoint(O, N, p);

    // glm::vec3 nearest = p + dist*(-N);

    // glm::vec3 An = glm::normalize(nearest - A);
    // glm::vec3 Bn = glm::normalize(nearest - B);


    // // Behind A, instead of between A and B.
    // if (glm::dot(AB, An) < 0.0f)
    // {
    //     nearest = A;
    // }

    // // Behind B, instead of between B and A.
    // else if (glm::dot(-AB, Bn) < 0.0f)
    // {
    //     nearest = B;
    // }

    // else
    // {
    // }

    // return nearest;
    return glm::vec3(0.0f);
}



glm::mat4 extractRotation0( const glm::mat4 &M )
{
    glm::vec3 r_scale;
    glm::quat r_rot;
    glm::vec3 r_trans;
    glm::vec3 r_skew;
    glm::vec4 r_persp;
    glm::decompose(M, r_scale, r_rot, r_trans, r_skew, r_persp);
    return glm::mat4_cast(r_rot);
}


glm::mat4 extractScale( const glm::mat4 &M )
{
    glm::vec3 r_scale;
    glm::quat r_rot;
    glm::vec3 r_trans;
    glm::vec3 r_skew;
    glm::vec4 r_persp;
    glm::decompose(M, r_scale, r_rot, r_trans, r_skew, r_persp);
    return glm::scale(glm::mat4(1.0f), r_scale);
}


bool
idk::geometry::capsuleRectIntersection( const glm::vec3 &c_pos,
                                        float c_bot, float c_top, float c_rad,
                                        const glm::mat4 &rect, glm::vec3 &res )
{
    glm::vec3 top    = c_pos + glm::vec3(0.001f, c_top, 0.0f);
    glm::vec3 mid    = c_pos;
    glm::vec3 bottom = c_pos - glm::vec3(0.0f,   c_bot, 0.0f);

    glm::vec3 rect_pos = glm::vec3(rect[3]);
    // glm::vec3 c_nearest = nearestPointOnLineSegment(bottom, top, rect_pos);

    res = glm::vec3(0.0f);
    glm::vec3 result = glm::vec3(0.0f);
    int count = 0;

    if (sphereRectIntersection(top, c_rad, rect, res))
    {
        res += result;
        count += 1;
    }

    if (sphereRectIntersection(mid, c_rad, rect, res))
    {
        res += result;
        count += 1;
    }

    if (sphereRectIntersection(bottom, c_rad, rect, result))
    {
        res += result;
        count += 1;
    }

    // if (sphereRectIntersection(c_nearest, c_rad, rect, res))
    // {
    //     res += result;
    //     count += 1;
    // }

    if (count > 0)
    {
        res /= count;
    }

    return count > 0;
}



bool
idk::geometry::pointInTriangle( const glm::vec3 &point, const Triangle &tri )
{
    return false;
}




bool
idk::geometry::sphereRectIntersection( glm::vec3 s_pos, float s_radius, const glm::mat4 &rect,
                                       glm::vec3 &res )
{
    glm::vec3 r_scale;
    glm::quat r_rot;
    glm::vec3 r_trans;
    glm::vec3 r_skew;
    glm::vec4 r_persp;
    glm::decompose(rect, r_scale, r_rot, r_trans, r_skew, r_persp);
    glm::mat3 R = glm::mat3(glm::mat4_cast(r_rot));


    glm::vec3 local_pos = glm::inverse(R) * (s_pos - r_trans);
    glm::vec3 rect_min  = r_scale * glm::vec3(-0.5f);
    glm::vec3 rect_max  = r_scale * glm::vec3(+0.5f);

    glm::vec3 local_collision = glm::clamp(local_pos, rect_min, rect_max);
    glm::vec3 world_collision = (R * local_collision) + r_trans;

    float dist = glm::distance(s_pos, world_collision);

    if (dist <= s_radius)
    {
        glm::vec3 dir  = glm::normalize(world_collision - s_pos);
        glm::vec3 edge = s_pos + s_radius*dir;

        res = world_collision - edge;

        return true;
    }

    return false;
}




bool ray_intersects_triangle( glm::vec3 ray_pos, glm::vec3 ray_dir,
                              glm::vec3 v0, glm::vec3 v1, glm::vec3 v2,
                              glm::vec3 *intersect_point )
{
    const float EPSILON = 0.0000001;
    glm::vec3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = v1 - v0;
    edge2 = v2 - v0;

    h = glm::cross(ray_dir, edge2);
    a = glm::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false;

    f = 1.0/a;
    s = ray_pos - v0;
    u = f * glm::dot(s, h);
    if (u < 0.0 || u > 1.0)
        return false;

    q = glm::cross(s, edge1);
    v = f * glm::dot(ray_dir, q);
    if (v < 0.0 || u + v > 1.0)
        return false;

    float t = f * glm::dot(edge2, q);
    if (t > EPSILON)
    {
        *intersect_point = ray_pos + ray_dir * t;
        return true;
    }

    else
        return false;
}


glm::vec3 ClosestPointOnLineSegment( glm::vec3 point, glm::vec3 A, glm::vec3 B )
{
    glm::vec3 AB = B - A;
    float t = glm::dot(point - A, AB) / glm::dot(AB, AB);
    return A + glm::min(glm::max(t, 0.0f), 1.0f) * AB;
}



bool
idk::geometry::capsuleTriangleIntersection( const glm::vec3 &capsule_pos, float bot, float top, float rad,
                                            const Triangle &tri, glm::vec3 &res )
{
    glm::vec3 center = capsule_pos - (bot) * glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 tri_center = (tri.v0 + tri.v1 + tri.v2) / 3.0f;
    glm::vec3 v0 = tri.v0 + rad*glm::normalize(v0 - tri_center);
    glm::vec3 v1 = tri.v1 + rad*glm::normalize(v1 - tri_center);
    glm::vec3 v2 = tri.v2 + rad*glm::normalize(v2 - tri_center);


    glm::vec3 N = glm::cross(v1 - v0, v2 - v0);
              N = glm::normalize(N);

    if (glm::dot(N, glm::normalize(center - v0)) < 0.0)
    {
        N *= -1.0f;
    }

    float plane_dist = geometry::distPlanePoint(v0, N, center);

    if (plane_dist < 0.0f)
    {
        return false;
    }

    if (plane_dist > rad)
    {
        return false;
    }

    res = (rad - plane_dist) * N;

    glm::vec3 intersection;
    bool intersects = ray_intersects_triangle(center, -res, v0, v1, v2, &intersection);

    if (intersects == false)
    {
        return false;
    }

    return true;
}




idk::geometry::CameraFrustum
idk::geometry::createCameraFrustum( float near, float far, float vfov, float aspect,
                                    const glm::vec3 &position,
                                    const glm::vec3 &front,
                                    const glm::vec3 &up,
                                    const glm::vec3 &right )
{
    idk::geometry::CameraFrustum frustum;

    const float halfVSide = far * tanf(vfov * .5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = far * front;


    frustum.positions[0]  = position + near*front;
    frustum.directions[0] = front;

    frustum.positions[1]  = position + far*front;
    frustum.directions[1] = -front;

    frustum.positions[2]  = position;
    frustum.directions[2] = glm::cross(far*front - halfHSide*right, up);

    frustum.positions[3]  = position;
    frustum.directions[3] = glm::cross(far*front + halfHSide*right, up);

    frustum.positions[4]  = position;
    frustum.directions[4] = glm::cross(far*front + halfVSide*up, right);

    frustum.positions[5]  = position;
    frustum.directions[5] = glm::cross(far*front - halfVSide*up, right);

    return frustum;
}



bool
idk::geometry::inFrustum( const CameraFrustum &frustum, const glm::mat4 &T, float radius )
{
    return true;

    glm::vec3 position = glm::vec3(T[3]);
    float scale = glm::length(T[0]);

    if (scale != scale)
    {
        return false;
    }

    for (int i=0; i<6; i++)
    {
        float dist = distPlanePoint(
            frustum.positions[i],
            frustum.directions[i],
            position
        );

        if (dist < -scale*radius)
        {
            return false;
        }
    }

    return true;
}


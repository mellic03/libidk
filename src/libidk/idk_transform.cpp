#include "idk_transform.hpp"

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/rotate_vector.hpp>

idk::Transform::Transform()
{

}

idk::Transform::Transform( glm::mat4 m ): m_model_mat(m)
{

}


float *
idk::Transform::position_ptr()
{
    return reinterpret_cast<float *>(&m_model_mat[3]);
}

glm::vec3
idk::Transform::position()
{
    return glm::vec3(m_model_mat[3]);
}


void
idk::Transform::position( glm::vec3 v )
{
    translate(-position());
    translate(v);
}


glm::vec3
idk::Transform::scale()
{
    return glm::vec3(
        m_model_mat[0][0],
        m_model_mat[1][1],
        m_model_mat[2][2]
    );
}


glm::vec3
idk::Transform::front()
{
    return m_model_mat * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
}


glm::vec3
idk::Transform::right()
{
    return m_model_mat * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
}


void
idk::Transform::pointTowards( const glm::vec3 &p )
{
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    glm::vec3 z_axis = glm::normalize(p - position());
    glm::vec3 x_axis = glm::normalize(glm::cross(up, z_axis));
    glm::vec3 y_axis = glm::normalize(glm::cross(z_axis, x_axis));

    glm::mat4 rotationMatrix(
        glm::vec4(x_axis, 0.0f),
        glm::vec4(y_axis, 0.0f),
        glm::vec4(z_axis, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    m_point_to = rotationMatrix;
}



void
idk::Transform::translate(glm::vec3 t)
{
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), t);

    m_model_mat = translation * m_model_mat;
}


void
idk::Transform::localTranslate( glm::vec3 t )
{
    t = glm::mat3(m_model_mat) * t;

    // if (_ylock)
    // {
        float length = glm::length(t);
        t.y = 0.000000001f; // Ensure length != 0
        t = length * glm::normalize(t);
    // }

    translate(t);
}


void
idk::Transform::pitch( float f )
{
//     m_view = glm::rotate(m_view, f, _right);
//     _front = glm::inverse(m_view) * _default_front;
//     _up = glm::inverse(m_view) * _default_up;

    glm::mat4 rot = glm::rotate(f, glm::vec3(1.0f, 0.0f, 0.0f));
    m_model_mat = m_model_mat * rot;
}


// void
// idk::Transform::roll( float f )
// {
    // m_view = glm::rotate(m_view, f, _front);

    // // if (_noroll == false)
    // // {
    //     _right = glm::inverse(m_view) * _default_right;
    //     _up = glm::inverse(m_view) * _default_up;
    // }
// }


void
idk::Transform::yaw( float f )
{
    glm::mat4 rot = glm::rotate(f, glm::inverse(glm::mat3(m_model_mat)) * glm::vec3(0.0f, 1.0f, 0.0f));
    m_model_mat = m_model_mat * rot;

    // if (_ylock)
    //     m_view = glm::rotate(m_view, f, glm::vec3(0.0f, 1.0f, 0.0f));
    // // else
    // //     m_view = glm::rotate(m_view, f, _up);

    // _right = glm::inverse(m_view) * _default_right;
    // _front = glm::inverse(m_view) * _default_front;
}



void
idk::Transform::scale(glm::vec3 s)
{
    m_scale = glm::vec3(m_scale.x*s.x, m_scale.y*s.y, m_scale.z*s.z);
}


void
idk::Transform::rotateX(float x)
{
    glm::quat rotX = glm::quat(glm::vec3(x, 0.0f, 0.0f));
    m_rotation = glm::mat4_cast(rotX) * m_rotation;
}

void
idk::Transform::rotateY(float y)
{
    glm::quat rotY = glm::quat(glm::vec3(0.0f, y, 0.0f));
    m_rotation = glm::mat4_cast(rotY) * m_rotation;
 
    // m_front = glm::mat3(m_model_mat) * m_front;
}

void
idk::Transform::rotateZ(float z)
{
    glm::quat rotZ = glm::quat(glm::vec3(0.0f, 0.0f, z));
    m_rotation = glm::mat4_cast(rotZ) * m_rotation;
 
    // m_rotation = glm::rotate(m_rotation, z, glm::vec3(0.0f, 0.0f, 1.0f));
    // glm::quat rotZ = glm::quat(glm::vec3(0.0f, 0.0f, z));
    // _model_mat = _model_mat * glm::mat4_cast(rotZ);
}


void
idk::Transform::rotate(glm::vec3 v)
{
    glm::quat rot = glm::quat(v);
    m_rotation = m_rotation * glm::mat4_cast(rot);
}


glm::mat4
idk::Transform::modelMatrix()
{
    // glm::mat4 model_mat = glm::translate(glm::mat4(1.0f), _position) * glm::mat4_cast(_orientation);
    // model_mat = glm::scale(model_mat, _scale);

    // return glm::scale(m_rotation * m_model_mat, m_scale);
    return m_model_mat * m_point_to * m_rotation;
}


glm::mat4 &
idk::Transform::modelMat()
{
    // glm::mat4 model_mat = glm::translate(glm::mat4(1.0f), _position) * glm::mat4_cast(_orientation);
    // model_mat = glm::scale(model_mat, _scale);

    // return glm::scale(m_rotation * m_model_mat, m_scale);
    return m_model_mat;
}


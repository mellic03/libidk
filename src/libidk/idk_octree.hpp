#pragma once

#include "idk_allocator.hpp"
#include "idk_glm.hpp"


namespace idk
{
    template <typename T>
    class CullOctree;

};



template <typename T>
class idk::CullOctree
{
private:

    struct Octnode
    {
        T           data;
        glm::vec3   position;   // Center of node
        float       span;       // Width of node
        int         children[8];

        Octnode( const Octnode &parent, int octant, const T &d )
        {
            data     = d;
            position = CullOctree<T>::_shiftCenter(parent.position, octant);
            span     = parent.span / 2.0f;
            std::fill_n(children, 8, -1);
        };
    };


    idk::Allocator<Octnode> m_nodes;

    static int         _getOctant( const glm::vec3 &center, const glm::vec3 &pos );
    static glm::vec3   _shiftCenter( const glm::vec3 &center, int octant );
    void               _insert( int node_id, const T &, const glm::vec3 &pos, float radius );


public:

    IDK_ALLOCATOR_ACCESS(Node, idk::CullOctree<T>::Octnode, m_nodes);

    void insert( const T &data, const glm::vec3 &pos, float radius );

};



template <typename T>
int
idk::CullOctree<T>::_getOctant( const glm::vec3 &center, const glm::vec3 &pos )
{
    int octant = 0;

    if (pos.x < center.x) octant |= 1;
    if (pos.y < center.y) octant |= 2;
    if (pos.z < center.z) octant |= 4;

    return octant;
}


template <typename T>
glm::vec3
idk::CullOctree<T>::_shiftCenter( const glm::vec3 &center, int octant )
{
    glm::vec3 pos = center;


    return pos;
}


template <typename T>
void
idk::CullOctree<T>::_insert( int node_id, const T &data, const glm::vec3 &pos, float radius )
{
    Octnode &node = getNode(node_id);

    if (radius > node.span)
    {
        // sutoppu
    }


    int  octant   = _getOctant(node.position, pos);
    int &child_id = node.children[octant];

    if (child_id == -1)
    {
        child_id = createNode(Octnode(node, octant, pos));
    }

    _insert(child_id, data, pos, radius);
}



template <typename T>
void
idk::CullOctree<T>::insert( const T &data, const glm::vec3 &pos, float radius )
{
    _insert(0, data, pos, radius);
}


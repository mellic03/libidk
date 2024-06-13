#pragma once

#include "./idk_allocator.hpp"

#include <vector>
#include <string>


template <typename T>
class idk_map
{
private:
    struct Node
    {
        int data;
        std::vector<int> children;
        Node(): children(26, -1) {  };
    };

    idk::Allocator<Node> m_nodes;
    idk::Allocator<T>    m_data;

    Node *m_root = new Node();

    T   *_insert ( const char *str, int depth, int id );
    T   *_find   ( const char *str, int depth, int id );
    void _remove ( const char *str, int depth, int id );


public:

    T   *insert ( const std::string& );
    T   *find   ( const std::string& );
    void remove ( const std::string& );


    T &operator [ ] ( const std::string &str )
    {
        T *data = find(str);
    
        if (data == nullptr)
        {
            data = insert(str);
        }

        return *data;
    };

};




template <typename T>
T *idk_map<T>::_insert( const char *str, int depth, int id )
{
    if (depth == 0)
    {
        if (m_nodes.get(id).data == -1)
        {
            m_nodes.get(id).data = m_data.create();
        }

        return &node->data;
    }

    int idx = str[0] - 'a';

    if (node->children[idx] == -1)
    {
        node->children[idx] = m_nodes.create();
    }

    return _insert(&str[1], depth-1, node->children[idx]);
}


template <typename T>
T *idk_map<T>::insert( const std::string &str )
{
    return _insert(&str[0], str.length(), m_root);
}


template <typename T>
T *idk_map<T>::_find( const char *str, int depth, Node *&node )
{
    if (depth == 0)
    {
        return node->data;
    }

    int idx = str[0] - 'a';

    if (node->children[idx])
    {
        return _find(&str[1], depth-1, node->children[idx]);
    }

    return nullptr;
}


template <typename T>
T *idk_map<T>::find( const std::string &str )
{
    return _find(&str[0], str.length(), m_root);
}


template <typename T>
void idk_map<T>::remove( const std::string &str )
{
    if (find(str))
    {

    }
}



int main()
{
    idk_map<int> t;

    t["michael"] = 15;

    std::cout << t["michael"] << "\n";

    // t.insert("michael");
    // t.insert("gayass");

    // if (t.find("mic"))
    // {
    //     std::cout << "YEP!\n";
    // }

    // else
    // {
    //     std::cout << "NOPE!\n";
    // }


    return 0;
}



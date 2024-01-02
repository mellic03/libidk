#pragma once


namespace idk { template <typename T> class basic_singleton; };


/** Simple singleton base class.
 * 
*/
template <typename T>
class idk::basic_singleton
{
protected:
    static T *instance_ptr;
    basic_singleton() {  };

public:
    basic_singleton( const basic_singleton & ) = delete;
    static T &get();
};


template <typename T>
T *idk::basic_singleton<T>::instance_ptr = nullptr;


template <typename T>
T &
idk::basic_singleton<T>::get()
{
    if (instance_ptr == nullptr)
    {
        instance_ptr = new T();
    }

    return *instance_ptr;
};

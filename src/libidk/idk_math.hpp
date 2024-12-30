#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <string>


// float putInRange( float x )
// {
//     x = glm::mod(x + 3.14159f, 2.0f*3.14159f) - 3.14159f;
//     return x;
// }


// float lerpAngle( float u, float v, float p )
// {
//     return 
// }



namespace idk
{
    static constexpr float TAU = 6.2831855f;
    static constexpr float PI  = 3.1415926f;
    static constexpr float HPI = 1.5707964f;


    float mixRadians( float x, float y, float a );





    /**
     * Framerate independent lerp.
     */
    template <typename T> T         flerp( T x, T y, T dt, T a );


    template <typename T> T         min( T, T );
    template <typename T> T         max( T, T );
    template <typename T> T         clamp( T, T, T );
    template <typename T> void      swap( T&, T& );
                          int       roundup( int n, int multipleof );
                          float     distanceSq( glm::vec3 a, glm::vec3 b );


    // template <typename T, typename... Args>
    // void    print( std::string sep, T head, Args... );
    // void    print( std::string sep );

    glm::vec3 calculate_barycentric( float x, float y, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3 );
};


template <typename T>
T
idk::flerp( T x, T y, T dt, T a )
{
    return glm::mix(x, y, 1.0f - expf32(-dt * a));
}



template <typename T>
T
idk::min( T a, T b )
{
    return (a < b) ? a : b;
}


template <typename T>
T
idk::max( T a, T b )
{
    return (a > b) ? a : b;
}


template <typename T>
T
idk::clamp( T in_value, T min_value, T max_value )
{
    return idk::max(min_value, idk::min(in_value, max_value));    
}


template <typename T> void
idk::swap( T&a, T&b )
{
    T temp = a;
    a = b;
    b = temp;
}



// template <typename T, typename... Args> void
// idk::print( std::string sep, T head, Args... rest )
// {
//     std::cout << head << sep;
//     idk::print(sep, rest...);
// }




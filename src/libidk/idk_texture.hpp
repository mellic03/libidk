#pragma once


namespace idk
{
    template <typename T>
    T&
    idk_sampleNearest( int u, int v, T *data, int width, int height )
    {
        int x = u % width;
        int y = v % height;
        return data[width*y + x];
    }

    template <typename T>
    T
    idk_sampleBillinear( float u, float v, T *data, int width, int height )
    {
        u *= width;
        v *= height;

        float x_factor = u - floor(u);
        float y_factor = v - floor(v);

        int x0 = int(u+0) % width;
        int x1 = int(u+1) % width;
        int y0 = int(v+0) % height;
        int y1 = int(v+1) % height;

        T &u00 = idk_sampleNearest(x0, y0, data, width, height);
        T &u01 = idk_sampleNearest(x1, y0, data, width, height);
        T &u10 = idk_sampleNearest(x0, y1, data, width, height);
        T &u11 = idk_sampleNearest(x1, y1, data, width, height);

        T u0 = glm::mix(u00, u01, x_factor);
        T u1 = glm::mix(u10, u11, x_factor);

        return glm::mix(u0, u1, y_factor);
    }
}


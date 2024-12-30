#pragma once

#include "./idk_sdl2.hpp"

namespace idk
{
    class Window;
    class GLContext;
}


class idk::Window
{
public:
    SDL_Window *sdl_win;
    int width, height;

    Window( const char *name, int w, int h, bool resizable=true, bool hidden=false );
    void resize( int w, int h );
    void swapWindow();

};


class idk::GLContext
{
private:
    idk::Window &m_win;
    void _init( idk::Window &win, int gl_major, int gl_minor );

public:
    int major, minor;
    SDL_GLContext sdl_ctx;

    GLContext( idk::Window &win, int gl_major, int gl_minor );
    void reload();
};


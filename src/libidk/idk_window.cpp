#include "idk_window.hpp"

#include "./GL/common.hpp"
#include <iostream>


idk::Window::Window( const char *name, int w, int h, bool resizable, bool hidden )
:   width(w),
    height(h)
{
    Uint32 sdl_flags = SDL_WINDOW_OPENGL;

    if (resizable) sdl_flags |= SDL_WINDOW_RESIZABLE;
    if (hidden)    sdl_flags |= SDL_WINDOW_HIDDEN;

    sdl_win = SDL_CreateWindow(
        name,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        w, h,
        sdl_flags
    );

}


void
idk::Window::resize( int w, int h )
{
    width = w;
    height = h;
    SDL_SetWindowSize(sdl_win, w, h);
}


void
idk::Window::swapWindow()
{
    SDL_GL_SwapWindow(sdl_win);
}




idk::GLContext::GLContext( idk::Window &win, int gl_major, int gl_minor )
:   m_win(win),
    major(gl_major),
    minor(gl_minor)
{
    _init(win, gl_major, gl_minor);
}


void
idk::GLContext::_init( idk::Window &win, int gl_major, int gl_minor )
{
    sdl_glctx = SDL_GL_CreateContext(win.sdl_win);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor);

    SDL_GL_MakeCurrent(win.sdl_win, sdl_glctx);
    SDL_GL_SetSwapInterval(0);
    SDL_SetRelativeMouseMode(SDL_FALSE);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error initializing glew\n";
        exit(1);
    }

    std::cout
        << "OpenGL version "
        << gl_major << "." << gl_minor
        << "\n";

}


void
idk::GLContext::reload()
{
    SDL_GL_DeleteContext(sdl_glctx);
    _init(m_win, major, minor);
}



// SDL_Window *
// SDL2_WindowSystem::createWindow( const char *name,
//                                  uint32_t flags  = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE,
//                                  int      width  = 512,
//                                  int      height = 512 )
// { 
//     SDL_Window *window = SDL_CreateWindow(
//         name,
//         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//         width, height,
//         flags
//     );

//     return window;
// }


// void
// SDL2_WindowSystem::destroyWindow( SDL_Window *window )
// {
//     SDL_DestroyWindow(window);
// }

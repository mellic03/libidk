// #include "idk_gl_headless.hpp"

// #include "GL/common.hpp"


// void
// idk::initHeadlessGLContext( int major, int minor )
// {
//     if (SDL_Init(SDL_INIT_VIDEO) < 0)
//     {
//         // std::cout << "Error creating window\n";
//         exit(1);
//     }

//     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24);
//     SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);


//     Uint32 sdl_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN;

//     SDL_Window *window = SDL_CreateWindow(
//         "",
//         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//         16, 16,
//         sdl_flags
//     );


//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);


//     SDL_GLContext glcontext = SDL_GL_CreateContext(window);
//     SDL_GL_MakeCurrent(window, glcontext);
//     SDL_GL_SetSwapInterval(0);
//     SDL_SetRelativeMouseMode(SDL_FALSE);

//     if (glewInit() != GLEW_OK)
//     {
//         // std::cout << "Error initializing glew\n";
//         exit(1);
//     }

// }
#pragma once

#include "idk_platform.hpp"
#define  IDK_SDL2

// Determine include path
// ---------------------------------------------------------------------------------------------
#ifdef IDK_UNIX
    #define IDK_SDL2_INCLUDE_PATH <SDL2/SDL.h>

#elif defined(IDK_WINDOWS)
    #define IDK_SDL2_INCLUDE_PATH <SDL.h>

#endif
// ---------------------------------------------------------------------------------------------

#include IDK_SDL2_INCLUDE_PATH


namespace idk::Keycode
{
    enum idk_Keycode
    {
        A               = SDL_SCANCODE_A,
        B               = SDL_SCANCODE_B,
        C               = SDL_SCANCODE_C,
        D               = SDL_SCANCODE_D,
        E               = SDL_SCANCODE_E,
        F               = SDL_SCANCODE_F,
        G               = SDL_SCANCODE_G,
        H               = SDL_SCANCODE_H,
        I               = SDL_SCANCODE_I,
        J               = SDL_SCANCODE_J,
        K               = SDL_SCANCODE_K,
        L               = SDL_SCANCODE_L,
        M               = SDL_SCANCODE_M,
        N               = SDL_SCANCODE_N,
        O               = SDL_SCANCODE_O,
        P               = SDL_SCANCODE_P,
        Q               = SDL_SCANCODE_Q,
        R               = SDL_SCANCODE_R,
        S               = SDL_SCANCODE_S,
        T               = SDL_SCANCODE_T,
        U               = SDL_SCANCODE_U,
        V               = SDL_SCANCODE_V,
        W               = SDL_SCANCODE_W,
        X               = SDL_SCANCODE_X,
        Y               = SDL_SCANCODE_Y,
        Z               = SDL_SCANCODE_Z,

        SPACE           = SDL_SCANCODE_SPACE,
        LCTRL           = SDL_SCANCODE_LCTRL,
        LSHIFT          = SDL_SCANCODE_LSHIFT,
        LALT            = SDL_SCANCODE_LALT,
        ESCAPE          = SDL_SCANCODE_ESCAPE,

        NUM_KEYCODES    = SDL_NUM_SCANCODES
    };
};


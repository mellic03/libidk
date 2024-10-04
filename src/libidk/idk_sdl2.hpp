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


namespace idk
{
    struct internal_keycode
    {
        enum Keycode: uint32_t
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
            LEFT            = SDL_SCANCODE_LEFT,
            RIGHT           = SDL_SCANCODE_RIGHT,
            UP              = SDL_SCANCODE_UP,
            DOWN            = SDL_SCANCODE_DOWN,

            N1               = SDL_SCANCODE_1,
            N2               = SDL_SCANCODE_2,
            N3               = SDL_SCANCODE_3,
            N4               = SDL_SCANCODE_4,
            N5               = SDL_SCANCODE_5,
            N6               = SDL_SCANCODE_6,
            N7               = SDL_SCANCODE_7,
            N8               = SDL_SCANCODE_8,
            N9               = SDL_SCANCODE_9,
            N0               = SDL_SCANCODE_0,


            F1              = SDL_SCANCODE_F1,
            F2              = SDL_SCANCODE_F2,
            F3              = SDL_SCANCODE_F3,
            F4              = SDL_SCANCODE_F4,
            F5              = SDL_SCANCODE_F5,
            F7              = SDL_SCANCODE_F7,
            F8              = SDL_SCANCODE_F8,
            F9              = SDL_SCANCODE_F9,
            F10             = SDL_SCANCODE_F10,
            F11             = SDL_SCANCODE_F11,
            F12             = SDL_SCANCODE_F12,

            SPACE           = SDL_SCANCODE_SPACE,
            LCTRL           = SDL_SCANCODE_LCTRL,
            LSHIFT          = SDL_SCANCODE_LSHIFT,
            LALT            = SDL_SCANCODE_LALT,
            ESCAPE          = SDL_SCANCODE_ESCAPE,
            TAB             = SDL_SCANCODE_TAB,

            PERIOD          = SDL_SCANCODE_PERIOD,
            BACKSPACE       = SDL_SCANCODE_BACKSPACE,

            NUM_KEYCODES    = SDL_NUM_SCANCODES
        };
    };


    using Keycode = internal_keycode::Keycode;

};


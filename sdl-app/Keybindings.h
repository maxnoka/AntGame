#pragma once
#include <SDL.h>

// Add new SDL keybindings here and add to InputHandler, as well as 
// whoever consumes the input (see e.g. Camera::OnMessage)

namespace Keybindings {
    namespace Navigation {
        namespace Left {
            constexpr auto kCode = SDLK_LEFT;
        }
        namespace Right {
            constexpr auto kCode = SDLK_RIGHT;
        }
        namespace Up {
            constexpr auto kCode = SDLK_UP;
        }
        namespace Down {
            constexpr auto kCode = SDLK_DOWN;
        }
        namespace ZoomIn {
            constexpr auto kCode = SDLK_z;
        }
        namespace ZoomOut {
            constexpr auto kCode = SDLK_x;
        }
    }

    namespace Simulation {
        namespace ToggleSim {
            constexpr auto kCode = SDLK_SPACE;
        }
    }

    namespace Debug {
        namespace ToggleDebug {
            constexpr auto kCode = SDLK_d;
        }
    }
}

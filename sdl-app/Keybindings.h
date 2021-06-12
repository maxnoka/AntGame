#include <SDL.h>

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
}
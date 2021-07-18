#include "Game.h"

#include <easyloggingpp/easylogging++.h>
#include <scopeguard/scopeguard.hpp>
#include <SDL.h>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

INITIALIZE_EASYLOGGINGPP

constexpr int kScreenWidth = 800;
constexpr int kScreenHeight = 600;

int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG(ERROR) << "SDL could not be initialized."
            << "SDL_Error: " << SDL_GetError();
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0")) {
        LOG(ERROR) << "SDL can not disable compositor bypass.";
        return 0;
    }
#endif

    SDL_Window* window = SDL_CreateWindow(
        "AntGame",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        kScreenWidth, kScreenHeight,
        SDL_WINDOW_SHOWN);
    if(!window) {
        LOG(ERROR) << "Window could not be created."
            << "SDL_Error: " << SDL_GetError();
        return 1;
    }
    auto destroyWindow = sg::make_scope_guard(
        [window](){ if (window) { SDL_DestroyWindow(window); } }
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        LOG(ERROR) << "Renderer could not be created."
            << "SDL_Error: " << SDL_GetError();
        return 1;
    }
    auto destroyRenderer = sg::make_scope_guard(
        [renderer](){ if (renderer) { SDL_DestroyRenderer(renderer); } }
    );

    Game antGame(kScreenWidth, kScreenHeight, renderer);

    bool shouldQuit = false;
    LOG(INFO) << "Starting game loop";
    while(!shouldQuit) {
        SDL_Event e;

        antGame.ProcessInput();

        // Initialize renderer color white for the background
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        antGame.Render();
        // Update screen
        SDL_RenderPresent(renderer);

        antGame.Update();

        // std::this_thread::sleep_for(1s);
        shouldQuit = antGame.ShouldQuit();
    }

    LOG(INFO) << "Quitting";
    // Quit SDL
    SDL_Quit();

    return 0;
}

#include "Game.h"

#include <easyloggingpp/easylogging++.h>
#include <SDL.h>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

INITIALIZE_EASYLOGGINGPP

// Define screen dimensions
constexpr int kScreenWidth = 800;
constexpr int kScreenHeight = 600;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG(ERROR) << "SDL could not be initialized!\n"
            << "SDL_Error: " << SDL_GetError();
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0")) {
        LOG(ERROR) << "SDL can not disable compositor bypass!";
        return 0;
    }
#endif

    // Create window
    SDL_Window *window = SDL_CreateWindow(
        "Basic C SDL project",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        kScreenWidth, kScreenHeight,
        SDL_WINDOW_SHOWN);

    if(!window) {
        LOG(ERROR) << "Window could not be created!\n"
            << "SDL_Error: " << SDL_GetError();
    }
    else {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer) {
            LOG(ERROR) << "Renderer could not be created!\n"
                << "SDL_Error: " << SDL_GetError();
        }
        else {
            Game antGame(kScreenWidth, kScreenHeight);

            bool shouldQuit = false;
            LOG(INFO) << "Starting game loop";
            while(!shouldQuit) {
                SDL_Event e;

                antGame.ProcessInput();

                // Initialize renderer color white for the background
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);
                // Set renderer color red to draw the square
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                antGame.Render(renderer);
                // Update screen
                SDL_RenderPresent(renderer);

                antGame.Update();

                std::this_thread::sleep_for(16ms);
                shouldQuit = antGame.ShouldQuit();
            }
            LOG(INFO) << "Quitting";
            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }
        // Destroy window
        SDL_DestroyWindow(window);
    }
    // Quit SDL
    SDL_Quit();

    return 0;
}

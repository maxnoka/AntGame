#include "InputHandler.h"

#include <iostream>
#include <algorithm>

void InputHandler::Keyboard() {
    for (auto& [_, v] : m_keysdown) v = false;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_quit = true;
            break;
        case SDL_KEYDOWN:
            m_keysheld[event.key.keysym.sym] = true;
            m_keysdown[event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            m_keysheld[event.key.keysym.sym] = false;
            break;
        default:
            break;
        }
    }
}

void InputHandler::HandleInput() {
    if(m_keysdown[SDLK_SPACE]) {
        m_simrun = !m_simrun;
    }

    if(m_keysdown[SDLK_F2]) {
        m_simrun = !m_simrun;
    }
}

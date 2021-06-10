#include "InputHandler.h"
#include "Camera.h"

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
            
        case SDL_KEYUP:
            m_keysheld[event.key.keysym.sym] = false;
            break;
        default:
            {};
        }
    }
}

void InputHandler::HandleInput() {
    m_zoominc = 0;
    m_xposmove = 0;
    m_yposmove = 0;
    
    if(m_keysdown[SDLK_SPACE]) {
        m_simrun = !m_simrun;
    }

    if(m_keysdown[SDLK_F2]) {
        m_simrun = !m_simrun;
    }

    if(m_keysdown[SDLK_z]) {
        m_zoominc = 1;
    }

    if(m_keysdown[SDLK_x]) {
        m_zoominc = -1;
    }

    if(m_keysdown[SDLK_RIGHT]) {
        ++m_xposmove;
    }

    if(m_keysdown[SDLK_LEFT]) {
        --m_xposmove;
    }

    if(m_keysdown[SDLK_UP]) {
       --m_yposmove;
    }

    if(m_keysdown[SDLK_DOWN]) {
        ++m_yposmove;
    }
}

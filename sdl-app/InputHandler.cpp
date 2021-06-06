#include "InputHandler.h"


#include <iostream>
#include <algorithm>


void InputHandler::Keyboard() {

    for (auto& [_, v] : m_keysdown) v = false;
    


   // message processing loop
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    

        // check for messages
        switch (event.type) {
            // check for keypresses

        case SDL_QUIT:
            m_quit = true; // set game state to done,(do what you want here)
            break;
        case SDL_KEYDOWN:
            //std::cout << event.key.keysym.sym << std::endl;
            m_keysheld[event.key.keysym.sym] = true;
            m_keysdown[event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
                m_keysheld[event.key.keysym.sym] = false;
            
            break;
        default:
            break;
        }
    } // end of message processing 

}


void InputHandler::HandleInput() {

    if(m_keysdown[SDLK_SPACE]) {
        m_simrun = !m_simrun;
    }

    if(m_keysdown[SDLK_F2]) {
        m_simrun = !m_simrun;
    }
}
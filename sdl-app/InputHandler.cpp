#include "InputHandler.h"

#include <SDL.h>
#include <algorithm>

bool isvalidkey(SDL_KeyboardEvent keycode){
    return keycode.keysym.sym < 122 && keycode.keysym.sym >= 0;
}

void InputHandler::Keyboard() {


    std::fill(m_KEYSdown.begin(), m_KEYSdown.end(), 0);

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
            if (isvalidkey(event.key) && event.key.repeat == 0){
                m_KEYS_held[event.key.keysym.sym] = true;
                m_KEYSdown[event.key.keysym.sym] = true;

            }
            break;
        case SDL_KEYUP:
            if (isvalidkey(event.key)){
                m_KEYS_held[event.key.keysym.sym] = false;
            }
            break;
        default:
            break;
        }
    } // end of message processing 

}


void InputHandler::HandleInput() {

    if(m_KEYSdown[SDLK_SPACE]) {
        m_simrun = !m_simrun;
    }
}
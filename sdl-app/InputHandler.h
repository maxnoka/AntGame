#pragma once

#include <map>
#include <SDL.h>

class InputHandler {
public:
    InputHandler()
    : m_keysheld()
    , m_keysdown()
    , m_simrun(false)
    , m_quit(false)
    {
        m_keysheld[SDLK_SPACE] = false;
        m_keysheld[SDLK_F2] = false;
        m_keysdown = m_keysheld;
    }

    void Keyboard();
    void HandleInput();
    bool GetSimrun() { return m_simrun; }
    bool GetQuite() { return m_quit; }

private:
    std::map<int, bool> m_keysheld;
    std::map<int, bool> m_keysdown;
    bool m_simrun;
    bool m_quit;
};

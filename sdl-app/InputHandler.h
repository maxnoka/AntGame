#pragma once

#include <map>
#include <SDL.h>

class InputHandler {
public:
    InputHandler()
    : m_keysheld()
    , m_keysdown()
    , m_simrun(false)
    , m_zoominc(0)
    , m_xposmove(0)
    , m_yposmove(0)
    , m_quit(false)
    {
        m_keysheld[SDLK_SPACE] = false;
        m_keysheld[SDLK_F2] = false;
        m_keysheld[SDLK_KP_PLUS] = false;
        m_keysheld[SDLK_KP_MINUS] = false;

        m_keysheld[SDLK_RIGHT] = false;
        m_keysheld[SDLK_LEFT] = false;
        m_keysheld[SDLK_UP] = false;
        m_keysheld[SDLK_DOWN] = false;

        m_keysdown = m_keysheld;
    }

    void Keyboard();
    void HandleInput();

    bool GetSimrun() { return m_simrun; }
    bool GetQuit() { return m_quit; }
    int GetZoominc() { return m_zoominc; }
    int GetXmove() { return m_xposmove; }
    int GetYmove() { return m_yposmove; }

private:
    std::map<int, bool> m_keysheld;
    std::map<int, bool> m_keysdown;
    bool m_simrun;
    int m_zoominc;
    int m_xposmove;
    int m_yposmove;
    bool m_quit;
};

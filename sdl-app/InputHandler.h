#pragma once

#include <vector>

class InputHandler {
public:

    InputHandler()
    : m_KEYS_held(122, false)
    , m_KEYSdown(122, false)
    , m_simrun(false)
    , m_quit(false)
    {}

    void Keyboard();
    void HandleInput();
    bool get_simrun() {
        return m_simrun;
    }
    bool get_quit() {
        return m_quit;
    }

private:
    std::vector<bool> m_KEYS_held;
    std::vector<bool> m_KEYSdown;
    bool m_simrun;
    bool m_quit;
};
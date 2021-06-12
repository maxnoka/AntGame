#include "InputHandler.h"
#include "Camera.h"
#include "Keybindings.h"

#include <iostream>
#include <algorithm>

InputHandler::InputHandler()
    : IMessageSource<KeysDict>()
    , IMessageSource<MiscInput>()
    , m_keysSubscribers()
    , m_miscSubscribers()
    , m_keysheld()
    , m_keysdown()
{
    {
        using namespace Keybindings::Navigation;
        m_keysheld[Left::kCode] = false;
        m_keysheld[Right::kCode] = false;
        m_keysheld[Up::kCode] = false;
        m_keysheld[Down::kCode] = false;
        m_keysheld[ZoomIn::kCode] = false;
        m_keysheld[ZoomOut::kCode] = false;
    }
    {
        using namespace Keybindings::Simulation;
        m_keysheld[ToggleSim::kCode] = false;
    }

    m_keysdown = m_keysheld;
}

void InputHandler::Subscribe(IMessageSubscriber<KeysDict>* subscriber) {
    m_keysSubscribers.push_back(subscriber);
}

void InputHandler::Subscribe(IMessageSubscriber<MiscInput>* subscriber) {
    m_miscSubscribers.push_back(subscriber);
}

void InputHandler::HandleInput() {
    for (auto& [_, v] : m_keysdown) v = false;

    SDL_Event event;
    bool receivedKeyEvent = false;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            DispatchMisc(MiscInput::Quit);
            break;
        case SDL_KEYDOWN:
            m_keysheld[event.key.keysym.sym] = true;
            m_keysdown[event.key.keysym.sym] = true;
            receivedKeyEvent = true;
            break;
        case SDL_KEYUP:
            m_keysheld[event.key.keysym.sym] = false;
            receivedKeyEvent = true;
            break;
        default:
            break;
        }
    }

    if (receivedKeyEvent) {
        DispatchKeys();
    }
}

void InputHandler::DispatchMisc(const MiscInput input) const {
    for (auto subscriber : m_miscSubscribers) {
        subscriber->OnMessage(input);
    }
}


void InputHandler::DispatchKeys() const {
    for (auto subscriber : m_keysSubscribers) {
        subscriber->OnMessage(m_keysdown);
    }
}

#pragma once

#include "MessagePassing.h"

#include <map>
#include <vector>
#include <SDL.h>

#define ANTGAME_TRY_GET_KEY(map, key, OnTrue) \
    try { \
        if (map.at(key)) { \
            OnTrue; \
        } \
    } \
    catch (const std::out_of_range&) { }

using KeysDict = std::map<int, bool>;

enum class MiscInput {
    Quit = 0,
};

class InputHandler final 
    : public IMessageSource<KeysDict>
    , public IMessageSource<MiscInput> {
public:
    InputHandler();

    void SubscribeToKeys(IMessageSubscriber<KeysDict>* subscriber) { Subscribe(subscriber); }
    void SubscribeToMiscInput(IMessageSubscriber<MiscInput>* subscriber) { Subscribe(subscriber); }
    void HandleInput();

private:
    virtual void Subscribe(IMessageSubscriber<KeysDict>* subscriber) override;
    virtual void Subscribe(IMessageSubscriber<MiscInput>* subscriber) override;
    void DispatchKeys() const;
    void DispatchMisc(const MiscInput input) const;

    std::vector< IMessageSubscriber<KeysDict>* > m_keysSubscribers;
    std::vector< IMessageSubscriber<MiscInput>* > m_miscSubscribers;

    KeysDict m_keysheld;
    KeysDict m_keysdown;
};

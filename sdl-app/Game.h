#pragma once

#include "MessagePassing.h"
#include "InputHandler.h"
#include "Camera.h"
#include "TreeRenderer.h"
#include "TextRenderer.h"

#include <antgame/World.h>

#include <SDL.h>

class Game final 
    : public IMessageSubscriber<KeysDict>
    , public IMessageSubscriber<MiscInput> {
    friend class WorldObjectRenderer;
    friend class TreeRenderer;
    friend class TextRenderer;
public:
    Game(int screenWidth, int screenHeight, SDL_Renderer* renderer);

    virtual void OnMessage(const KeysDict& keysDown) override;
    virtual void OnMessage(const MiscInput& input) override;

    void ProcessInput();
    void Render();
    void Update() { if(m_runSim) m_world.Update(); }
    bool ShouldQuit() { return m_shouldQuit; }

private:
    Camera m_camera;
    World m_world;
    InputHandler m_inputHandler;
    TreeRenderer m_treeRenderer;
    TextRenderer m_textRenderer;
    SDL_Renderer* m_renderer;

    // Game State
    bool m_runSim;
    bool m_debugMode;
    bool m_shouldQuit;
};

#include "MessagePassing.h"
#include "InputHandler.h"
#include "Camera.h"
#include "WorldObjectRenderer.h"

#include <antgame/World.h>

#include <SDL.h>

class Game final 
    : public IMessageSubscriber<KeysDict>
    , public IMessageSubscriber<MiscInput> {
    friend class WorldObjectRenderer;
public:
    Game(int screenWidth, int screenHeight, SDL_Renderer* renderer);


    virtual void OnMessage(const KeysDict& keysDown) override;
    virtual void OnMessage(const MiscInput& input) override;

    void ProcessInput();
    void Render() const;
    void Update() { if(m_runSim) m_world.Update(); }
    bool ShouldQuit() { return m_shouldQuit; }

private:
    Camera m_camera;
    WorldObjectRenderer m_worenderer;
    SDL_Renderer* m_renderer;
    World m_world;
    InputHandler m_inputHandler;

    // Game State
    bool m_runSim;
    bool m_debugMode;
    bool m_shouldQuit;
};

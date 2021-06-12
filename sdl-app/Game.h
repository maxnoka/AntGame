#include "MessagePassing.h"
#include "InputHandler.h"
#include "Camera.h"

#include <antgame/World.h>

#include <SDL.h>

class Game final 
    : public IMessageSubscriber<KeysDict>
    , public IMessageSubscriber<MiscInput> {
public:
    Game(int screenWidth, int screenHeight);

    virtual void OnMessage(const KeysDict& keysDown) override;
    virtual void OnMessage(const MiscInput& input) override;

    void ProcessInput();
    void Render(SDL_Renderer* renderer) const;
    void Update() { if(m_runSim) m_world.Update(); }
    bool ShouldQuit() { return m_shouldQuit; }

private:
    Camera m_camera;
    World m_world;
    InputHandler m_inputHandler;

    // Game State
    bool m_runSim;
    bool m_shouldQuit;
    void ToggleRunSim() noexcept;
};
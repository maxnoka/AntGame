#include "Game.h"
#include "Keybindings.h"
#include "WorldObjectRenderer.h"
#include "TreeRenderer.h"

#include <antgame/Ant.h>
#include <antgame/FoodSource.h>

#include <easyloggingpp/easylogging++.h>

Game::Game(int screenWidth, int screenHeight, SDL_Renderer* renderer) 
    : IMessageSubscriber<KeysDict>()
    , IMessageSubscriber<MiscInput>()
    , m_camera(Point(0., 0.), 0, 0., screenWidth, screenHeight)
    , m_world()
    , m_inputHandler()
    , m_treeRenderer(this)
    , m_textRenderer(this)
    , m_renderer(renderer)
    , m_runSim(false)
    , m_debugMode(false)
    , m_shouldQuit(false)
{ 
    m_inputHandler.SubscribeToKeys(&m_camera);
    m_inputHandler.SubscribeToKeys(this);
    m_inputHandler.SubscribeToMiscInput(this);

    // Add some ants
    for ( unsigned int i = 0 ; i < 1; ++i ) {
        Point point(2*i + 0.0f, 2*i + 0.0f);
        auto newObj = std::make_shared<Ant>(point, "Ant_" + std::to_string(i));
        m_world.QueueAddAgent(std::move(newObj));
    }

    for ( unsigned int i = 0 ; i < 20 ; ++i ) {
        Point point(2*i + 5.0f, 3*i + 7.0f);
        auto newObj = std::make_shared<Ant>(point, "Ant_" + std::to_string(i));
        m_world.QueueAddAgent(std::move(newObj));
    }

    // Add a food source
    Point point(5.f, 5.f);
    auto source = std::make_shared<FoodSource>(point, "Source_1", 6, 23);
    m_world.QueueAddAgent(std::move(source));

    m_world.FlushQueues();
}

void Game::Update() {
    if(!m_runSim) {
        return;
    }
    m_world.Update(); 
}

void Game::OnMessage(const KeysDict& keysDown) {
    using namespace Keybindings;
    ANTGAME_TRY_GET_KEY(keysDown, Simulation::ToggleSim::kCode,
        [this](){
            this->m_runSim = !this->m_runSim; 
            LOG(INFO) << "Sim " << (this->m_runSim ? "started" : "stopped");
        }())
    ANTGAME_TRY_GET_KEY(keysDown, Debug::ToggleDebug::kCode, 
        [this](){
            this->m_debugMode = !this->m_debugMode; 
            LOG(INFO) << "Debug mode " << (this->m_debugMode ? "enabled" : "disabled");
        }())
}

void Game::OnMessage(const MiscInput& input) { 
    switch (input) {
    case MiscInput::Quit:
        m_shouldQuit = true;
        break;
    default:
        break;;
    }
}

void Game::ProcessInput() {
    m_inputHandler.HandleInput();
}

void Game::Render() {
    m_treeRenderer.Render();
}

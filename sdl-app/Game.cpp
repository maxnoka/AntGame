#include "Game.h"
#include "Keybindings.h"
#include "WorldObjectRenderer.h"
#include "TreeRenderer.h"

#include <antgame/Ant.h>
#include <antgame/Plant.h>

#include <easyloggingpp/easylogging++.h>

Game::Game(int screenWidth, int screenHeight, SDL_Renderer* renderer) 
    : IMessageSubscriber<KeysDict>()
    , IMessageSubscriber<MiscInput>()
    , m_camera(Point(0., 0.), 0, 0., screenWidth, screenHeight)
    , m_world()
    , m_inputHandler()
    , m_runSim(false)
    , m_debugMode(false)
    , m_shouldQuit(false)
    , m_renderer(renderer)
    , m_worenderer(this)
{ 
    m_inputHandler.SubscribeToKeys(&m_camera);
    m_inputHandler.SubscribeToKeys(this);
    m_inputHandler.SubscribeToMiscInput(this);

    // Add some ants
    for ( unsigned int i = 0 ; i < 20 ; ++i ) {
        Point point(2*i + 0.0f, 2*i + 0.0f);
        auto newObj = std::make_shared<Ant>(point, "Ant_" + std::to_string(i));
        m_world.AddAgent(std::move(newObj));
    }

    for ( unsigned int i = 0 ; i < 20 ; ++i ) {
        Point point(2*i + 5.0f, 3*i + 7.0f);
        auto newObj = std::make_shared<Ant>(point, "Ant_" + std::to_string(i));
        m_world.AddAgent(std::move(newObj));
    }

    {
        Point point(7, 3);
        auto newObj = std::make_shared<Ant>(point, "Ant_6");
        m_world.AddAgent(std::move(newObj));
    }

    // Add some food
    for ( unsigned int i = 5 ; i < 10 ; ++i ) {
        Point point(i + 0.0f, 2.0f);
        auto newObj = std::make_shared<Plant>(point, "Plant_" + std::to_string(i), 5);
        m_world.AddObject(std::move(newObj));
    }
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
    TreeRenderer tr(this);
    tr.Render();
}

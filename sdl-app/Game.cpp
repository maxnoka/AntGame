#include "Game.h"
#include "Keybindings.h"

#include <antgame/Ant.h>

#include <easyloggingpp/easylogging++.h>

namespace {
    Box ExpandPointToRect(const WorldObject& point, float size) {
        auto min_x = point.GetPosX() - size / 2;
        auto min_y = point.GetPosY() - size / 2;
        auto max_x = point.GetPosX() + size / 2;
        auto max_y = point.GetPosY() + size / 2;
        return Box({min_x, min_y}, {max_x, max_y});
    }

    SDL_FRect BoxToFRectTransform(const Box& box, const Camera& cam) {
        auto min = cam.WorldToScreenTransform(box.min_corner());
        auto max = cam.WorldToScreenTransform(box.max_corner());

        return SDL_FRect { min.x, min.y, (max.x - min.x), (max.y - min.y)};
    }

    constexpr auto kDefaultSize = 0.5;
}

Game::Game(int screenWidth, int screenHeight) 
    : IMessageSubscriber<KeysDict>()
    , IMessageSubscriber<MiscInput>()
    , m_camera(Point(0., 0.), 0, 0., screenWidth, screenHeight)
    , m_world()
    , m_inputHandler()
    , m_runSim(false)
    , m_shouldQuit(false)
{ 
    m_inputHandler.SubscribeToKeys(&m_camera);
    m_inputHandler.SubscribeToKeys(this);
    m_inputHandler.SubscribeToMiscInput(this);

    for ( unsigned int i = 0 ; i < 10 ; ++i ) {
        // create a box
        Point point(i + 0.0f, i + 0.0f);
        auto newObj = std::make_shared<Ant>(point, std::to_string(i));
        m_world.AddObject(std::move(newObj));
    }
}

void Game::ToggleRunSim() noexcept {
    m_runSim = !m_runSim;
}

void Game::OnMessage(const KeysDict& keysDown) {
    using namespace Keybindings;
    ANTGAME_TRY_GET_KEY(keysDown, Simulation::ToggleSim::kCode, ToggleRunSim())
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

void Game::Render(SDL_Renderer* renderer) const {
    auto frustrum = m_camera.GetFrustrum();

    auto [objectsIt, objectsItEnd] = m_world.GetObjects(frustrum);
    std::vector<SDL_FRect> pointsToRender(std::distance(objectsIt, objectsItEnd));
    auto it = std::inserter(pointsToRender, pointsToRender.begin());
    std::transform(
        objectsIt,
        objectsItEnd,
        it,
        [this](const std::shared_ptr<WorldObject>& wobj) {
            auto rect = ExpandPointToRect(*wobj, kDefaultSize);
            return BoxToFRectTransform(rect, this->m_camera);
        } 
    );

    SDL_RenderDrawRectsF(
        renderer,
        pointsToRender.data(),
        pointsToRender.size()
    );
}
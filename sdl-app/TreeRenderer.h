#pragma once

#include "WorldObjectRenderer.h"

class Game;

class TreeRenderer final {
public:
    TreeRenderer(Game* game)
    : m_game(game)
    , m_worldObjectRenderer(game)
    { }

    void Render() const;

private:
    void RenderNodes() const;

    Game* m_game;
    const WorldObjectRenderer m_worldObjectRenderer;
};


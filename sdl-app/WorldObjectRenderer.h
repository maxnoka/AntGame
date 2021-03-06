#pragma once

#include <antgame/Visitor.h>

class Game;

class WorldObjectRenderer final : public Visitor {
public:
    WorldObjectRenderer(Game* game)
    : m_game(game)
    {}

    virtual void Visit(const Ant& visitee) const override final;
    virtual void Visit(const Food& visitee) const override final;
    virtual void Visit(const WorldObject& visitee) const override final;
    virtual void Visit(const Box& visitee) const override final;

private:
    Game* m_game;
};

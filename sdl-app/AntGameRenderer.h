#pragma once
#include <antgame/World.h>

#include "Camera.h"
#include <SDL.h>

void Render(SDL_Renderer* renderer, const World& world, const Camera& camera);

#include "enemy.hh"
#include "SDL2/SDL.h"

void My::Enemy::update() {
    ++_x;
    ++_y;
    _curFrame = int((SDL_GetTicks() / 100) * 6);
}
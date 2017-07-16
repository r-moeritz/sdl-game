#include "enemy.hh"
#include "SDL2/SDL.h"

My::Enemy::Enemy(const My::LoaderParams* pParams)
    : My::SDLGameObject(pParams) {}

void My::Enemy::update() {
  _position.setX(_position.x());
  _position.setY(_position.y());
  _curFrame = int((SDL_GetTicks() / 100) % 6);
}

void My::Enemy::clean() {}

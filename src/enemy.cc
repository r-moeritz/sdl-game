#include "enemy.hh"
#include "SDL2/SDL.h"

My::Enemy::Enemy(const My::LoaderParams* pParams, int numFrames)
  : My::SDLGameObject(pParams), _numFrames(numFrames) {
  _velocity.setY(2);
  _velocity.setX(0.001);
}

void My::Enemy::update() {
  _curFrame = int((SDL_GetTicks() / 100) % _numFrames);

  if (_position.y() < 0) {
    _velocity.setY(2);
  }
  else if (_position.y() > 400) {
    _velocity.setY(-2);
  }

  SDLGameObject::update();
}

void My::Enemy::clean() {}

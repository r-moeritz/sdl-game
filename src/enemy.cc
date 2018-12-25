#include "enemy.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

Enemy::Enemy(const LoaderParams* pParams, int numFrames)
  : SDLGameObject(pParams), _numFrames(numFrames) {
  _velocity.setY(2);
  _velocity.setX(0.001);
}

void Enemy::update() {
  _curFrame = int((SDL_GetTicks() / 100) % _numFrames);

  if (_position.y() < 0) {
    _velocity.setY(2);
  }
  else if (_position.y() > 400) {
    _velocity.setY(-2);
  }

  SDLGameObject::update();
}

void Enemy::clean() {}

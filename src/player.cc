#include "player.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

Player::Player(const LoaderParams* pParams, int numFrames)
  : SDLGameObject(pParams), _numFrames(numFrames) {

}

void Player::update() {
  _velocity.setX(0);
  _velocity.setY(0);

  handleInput();

  _curFrame = int((SDL_GetTicks() / 100) % _numFrames);

  SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput() {
  auto target = _pInputHandler->mousePosition();
  _velocity = target - _position;
  _velocity /= 50;
}

#include "player.hh"
#include "SDL2/SDL.h"

My::Player::Player(const My::LoaderParams* pParams)
  : My::SDLGameObject(pParams) {

}

void My::Player::update() {
  _velocity.setX(0);
  _velocity.setY(0);

  handleInput();

  _curFrame = int((SDL_GetTicks() / 100) % 6);

  SDLGameObject::update();
}

void My::Player::clean() {}

void My::Player::handleInput() {
  auto target = _pInputHandler->mousePosition();
  _velocity = target - _position;
  _velocity /= 50;
}

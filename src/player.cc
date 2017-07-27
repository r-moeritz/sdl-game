#include "player.hh"
#include "SDL2/SDL.h"

My::Player::Player(const My::LoaderParams* pParams)
  : My::SDLGameObject(pParams),
  _pInputHandler(My::InputHandler::Instance()) {}

void My::Player::update() {
  _velocity.setX(0);
  _velocity.setY(0);

  handleInput();

  _curFrame = int((SDL_GetTicks() / 100) % 6);

  SDLGameObject::update();
}

void My::Player::clean() {}

void My::Player::handleInput() {
  if (_pInputHandler->joysticksInitialized()) {
    if (_pInputHandler->x(0,1) != 0) {
      _velocity.setX(1 * _pInputHandler->x(0,1));
    }

    if (_pInputHandler->y(0,1) != 0) {
      _velocity.setY(1 * _pInputHandler->y(0,1));
    }

    if (_pInputHandler->x(0,2) != 0) {
      _velocity.setX(1 * _pInputHandler->x(0,2));
    }

    if (_pInputHandler->y(0,2) != 0) {
      _velocity.setY(1 * _pInputHandler->y(0,2));
    }
  }
}

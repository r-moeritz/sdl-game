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
    // Joystick input
    if (_pInputHandler->buttonState(0, 3)) {
      _acceleration.setX(_acceleration.x() + 1);
    }

    if (_pInputHandler->buttonState(0, 2)) {
      _acceleration.setX(_acceleration.x() - 1);
    }

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
  } else {
    // Keyboard input
    if (_pInputHandler->isKeyDown(SDL_SCANCODE_RIGHT)) {
      _velocity.setX(2);
    }

    if (_pInputHandler->isKeyDown(SDL_SCANCODE_LEFT)) {
      _velocity.setX(-2);
    }

    if (_pInputHandler->isKeyDown(SDL_SCANCODE_UP)) {
      _velocity.setY(-2);
    }

    if (_pInputHandler->isKeyDown(SDL_SCANCODE_DOWN)) {
      _velocity.setY(2);
    }
  }
}

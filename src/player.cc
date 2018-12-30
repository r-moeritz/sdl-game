#include "player.hh"
#include "sdlgameobject.hh"
#include "loaderparams.hh"
#include "inputhandler.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

struct Player::Impl : public SDLGameObject {

  Impl(const LoaderParams* pParams, int numFrames)
    : SDLGameObject(pParams),
      _numFrames(numFrames) {}

  void update() override {
    auto v = velocity();
    v.setX(0);
    v.setY(0);

    handleInput();

    currentFrame(int((SDL_GetTicks() / 100) % _numFrames));

    SDLGameObject::update();
  }

  void clean() override {}

private:

  int _numFrames;

  void handleInput() {
    auto pInputHandler = InputHandler::Instance();
    auto target = pInputHandler->mousePosition();

    auto v = target - position();
    v /= 50;

    velocity(v);
  }
};

Player::Player(const LoaderParams* pParams, int numFrames)
  : _pImpl(std::make_unique<Impl>(pParams, numFrames)) {}

Player::~Player() = default;
Player::Player(Player&&) = default;
Player& Player::operator=(Player&&) = default;

void Player::draw() {
  _pImpl->draw();
}

void Player::update() {
  _pImpl->update();
}

void Player::clean() {
  _pImpl->clean();
}

Vector2D Player::position() const {
  return _pImpl->position();
}

int Player::width() const {
  return _pImpl->width();
}

int Player::height() const {
  return _pImpl->height();
}

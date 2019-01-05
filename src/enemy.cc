#include "enemy.hh"
#include "sdlgameobject.hh"
#include "loaderparams.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

struct Enemy::Impl : public SDLGameObject {

  Impl(std::shared_ptr<LoaderParams> pParams, int numFrames)
    : SDLGameObject(pParams), _numFrames(numFrames) {
    auto v = velocity();
    v.setY(2);
    v.setX(0.001);
  }

  void update() override {
    auto cf = int((SDL_GetTicks() / 100) % _numFrames);
    currentFrame(cf);

    if (position().y() < 0) {
      velocity().setY(2);
    }
    else if (position().y() > 400) {
      velocity().setY(-2);
    }

    SDLGameObject::update();
  }

  void clean() override {}

private:

  int _numFrames;
};

Enemy::Enemy(std::shared_ptr<LoaderParams> pParams, int numFrames)
  : _pImpl(std::make_unique<Impl>(pParams, numFrames)) {}

Enemy::~Enemy() = default;
Enemy::Enemy(Enemy&&) = default;
Enemy& Enemy::operator=(Enemy&&) = default;

void Enemy::draw() {
  _pImpl->draw();
}

void Enemy::update() {
  _pImpl->update();
}

void Enemy::clean() {
  _pImpl->clean();
}

Vector2D Enemy::position() const {
  return _pImpl->position();
}

int Enemy::width() const {
  return _pImpl->width();
}

int Enemy::height() const {
  return _pImpl->height();
}

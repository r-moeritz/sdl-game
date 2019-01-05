#include "animatedgraphic.hh"
#include "sdlgameobject.hh"
#include "loaderparams.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

struct AnimatedGraphic::Impl : public SDLGameObject {

  Impl(std::shared_ptr<LoaderParams> pParams,
       int numFrames,
       int animSpeed)
    : SDLGameObject(pParams),
      _numFrames(numFrames),
      _animSpeed(animSpeed) {}

  void update() override {
    auto cf = int(((SDL_GetTicks() / (1000 / _animSpeed))
                   % _numFrames));
    currentFrame(cf);
  }

  void clean() override {
    // Nothing to do
  }

private:

  int _numFrames;
  int _animSpeed;
};

AnimatedGraphic::AnimatedGraphic(std::shared_ptr<LoaderParams> pParams,
                                 int numFrames,
                                 int animSpeed)
  : _pImpl(std::make_unique<Impl>(pParams, numFrames, animSpeed)) {}

AnimatedGraphic::~AnimatedGraphic() = default;
AnimatedGraphic::AnimatedGraphic(AnimatedGraphic&&) = default;
AnimatedGraphic& AnimatedGraphic::operator=(AnimatedGraphic&&) = default;

void AnimatedGraphic::draw() {
  _pImpl->draw();
}

void AnimatedGraphic::update() {
  _pImpl->update();
}

void AnimatedGraphic::clean() {
  _pImpl->clean();
}

Vector2D AnimatedGraphic::position() const {
  return _pImpl->position();
}

int AnimatedGraphic::width() const {
  return _pImpl->width();
}

int AnimatedGraphic::height() const {
  return _pImpl->height();
}

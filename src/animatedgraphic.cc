#include "animatedgraphic.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams,
                                     int numFrames,
                                     int animSpeed)
  : SDLGameObject(pParams),
  _numFrames(numFrames),
  _animSpeed(animSpeed) {
}

void AnimatedGraphic::update() {
  _curFrame = int(((SDL_GetTicks() / (1000 / _animSpeed))
                   % _numFrames));
}

void AnimatedGraphic::clean() {}

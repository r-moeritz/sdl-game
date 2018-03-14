#include "animatedgraphic.hh"
#include "SDL2/SDL.h"

My::AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams,
                                     int numFrames,
                                     int animSpeed)
  : My::SDLGameObject(pParams),
  _numFrames(numFrames),
  _animSpeed(animSpeed) {
}

void My::AnimatedGraphic::update() {
  _curFrame = int(((SDL_GetTicks() / (1000 / _animSpeed))
                   % _numFrames));
}

void My::AnimatedGraphic::clean() {}

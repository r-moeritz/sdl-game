#ifndef ANIMATEDGRAPHIC_HH
#define ANIMATEDGRAPHIC_HH

#include "sdlgameobject.hh"
#include "loaderparams.hh"

namespace My {
  class AnimatedGraphic : public SDLGameObject {
  public:

    AnimatedGraphic(const LoaderParams*, int, int);

    virtual void update();
    virtual void clean();

  private:

    int _numFrames;
    int _animSpeed;
  };
}

#endif

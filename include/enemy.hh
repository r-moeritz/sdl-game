#ifndef ENEMY_HH
#define ENEMY_HH

#include "sdlgameobject.hh"
#include "loaderparams.hh"

namespace My {
  class Enemy : public SDLGameObject {
  public:

    Enemy(const LoaderParams*, int);

    virtual void update();
    virtual void clean();

  private:

    int _numFrames;
  };
}

#endif

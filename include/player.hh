#ifndef PLAYER_HH
#define PLAYER_HH

#include "sdlgameobject.hh"
#include "loaderparams.hh"

namespace MyGame {
  struct Player : public SDLGameObject {

    Player(const LoaderParams*, int);

    virtual void update();
    virtual void clean();

  private:

    int _numFrames;
    void handleInput();
  };
}

#endif

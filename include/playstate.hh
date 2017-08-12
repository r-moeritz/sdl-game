#ifndef PLAYSTATE_HH
#define PLAYSTATE_HH

#include "gamestate.hh"

namespace My {
  class PlayState : public GameState {
  public:

    PlayState();

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
      return "PLAY";
    }
  };
}

#endif

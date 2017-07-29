#ifndef PLAYERSTATE_HH
#define PLAYERSTATE_HH

#include "gamestate.hh"

namespace My {
  class PlayerState : public GameState {
  public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
      return "PLAYER";
    }
  };
}

#endif

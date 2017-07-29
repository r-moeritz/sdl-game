#ifndef MENUSTATE_HH
#define MENUSTATE_HH

#include "gamestate.hh"

namespace My {
  class MenuState : public GameState {
  public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
      return "MENU";
    }
  };
}

#endif

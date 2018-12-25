#ifndef PAUSESTATE_HH
#define PAUSESTATE_HH

#include <memory>
#include <vector>
#include <string>
#include "gamestate.hh"

namespace MyGame {
  struct PauseState : public GameState {

    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
      return "PAUSE";
    }

  private:

    static void s_main();
    static void s_resume();

    std::vector<std::shared_ptr<GameObject>> _gameObjects;
  };
}

#endif

#ifndef PAUSESTATE_HH
#define PAUSESTATE_HH

#include <memory>
#include <vector>
#include <string>
#include "gamestate.hh"

namespace MyGame {
  struct PauseState : public GameState {

    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override {
      return "PAUSE";
    }

  private:

    static void s_main();
    static void s_resume();

    std::vector<std::shared_ptr<GameObject>> _gameObjects;
  };
}

#endif

#ifndef GAMESTATEMACHINE_HH
#define GAMESTATEMACHINE_HH

#include "gamestate.hh"
#include <vector>
#include <memory>
#include <string>

namespace MyGame {
  struct GameStateMachine {

    void update();
    void render();
    void clean();

    void changeState(std::shared_ptr<GameState>);
    bool pushState(std::shared_ptr<GameState>);
    bool popState();

    static GameStateMachine* Instance();

  private:

    GameStateMachine();

    static GameStateMachine* s_pInstance;

    std::vector<std::shared_ptr<GameState>> _gameStates;
    std::shared_ptr<GameState> currentState() const;

    bool enterState(std::shared_ptr<GameState>);
    bool exitCurrentState();
  };
}

#endif

#ifndef GAMESTATEMACHINE_HH
#define GAMESTATEMACHINE_HH

#include "gamestate.hh"
#include <vector>
#include <memory>

namespace My {
  class GameStateMachine {
  public:

    void pushState(GameState*);
    void changeState(GameState*);
    void popState();

  private:

    std::vector<std::shared_ptr<GameState>> _gameStates;

    std::shared_ptr<GameState> currentState() const;
  };
}

#endif

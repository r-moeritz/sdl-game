#ifndef GAMESTATEMACHINE_HH
#define GAMESTATEMACHINE_HH

#include <memory>

namespace MyGame {
  struct GameState;
  using GameStatePtr = std::shared_ptr<GameState>;

  struct GameStateMachine {

    ~GameStateMachine();
    GameStateMachine(GameStateMachine&&);
    GameStateMachine& operator=(GameStateMachine&&);

    void update();
    void render();
    void clean();

    void changeState(GameStatePtr);
    bool pushState(GameStatePtr);
    bool popState();

    static GameStateMachine* Instance();

  private:

    GameStateMachine();

    struct Impl;
    std::unique_ptr<Impl> _pImpl;

    static GameStateMachine* s_pInstance;
  };
}

#endif

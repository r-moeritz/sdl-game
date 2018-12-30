#ifndef GAMEOVERSTATE_HH
#define GAMEOVERSTATE_HH

#include "gamestate.hh"
#include <memory>
#include <string>

namespace MyGame {
  struct GameOverState : public GameState {

    GameOverState();
    ~GameOverState();
    GameOverState(GameOverState&&);
    GameOverState& operator=(GameOverState&&);

    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override;

  private:

    struct Impl;
    std::unique_ptr<Impl> _pImpl;
  };
}

#endif

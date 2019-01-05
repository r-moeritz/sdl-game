#ifndef PAUSESTATE_HH
#define PAUSESTATE_HH

#include <string>
#include <memory>
#include "gamestate.hh"

namespace MyGame {
  struct PauseState : public GameState {

    PauseState();
    ~PauseState();
    PauseState(PauseState&&);
    PauseState& operator=(PauseState&&);

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

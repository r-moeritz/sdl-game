#ifndef PLAYSTATE_HH
#define PLAYSTATE_HH

#include <memory>
#include "gamestate.hh"

namespace MyGame {
  struct PlayState : public GameState {

    PlayState();
    ~PlayState();
    PlayState(PlayState&&);
    PlayState& operator=(PlayState&&);

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

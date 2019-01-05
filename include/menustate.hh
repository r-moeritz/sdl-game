#ifndef MENUSTATE_HH
#define MENUSTATE_HH

#include <memory>
#include <string>
#include "gamestate.hh"

namespace MyGame {
  struct MenuState : public GameState {

    MenuState();
    ~MenuState();
    MenuState(MenuState&&);
    MenuState& operator=(MenuState&&);

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

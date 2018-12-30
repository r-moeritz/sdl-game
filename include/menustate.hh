#ifndef MENUSTATE_HH
#define MENUSTATE_HH

#include <memory>
#include <string>
#include <vector>
#include "gameobject.hh"
#include "gamestate.hh"
#include "texturemanager.hh"

namespace MyGame {
  struct MenuState : public GameState {

    MenuState();

    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override {
      return "MENU";
    }

  private:

    static void s_play();
    static void s_exit();

    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    TextureManager* _pTextureManager;
  };
}

#endif

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

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
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

#ifndef MENUSTATE_HH
#define MENUSTATE_HH

#include <memory>
#include <vector>
#include "gameobject.hh"
#include "gamestate.hh"
#include "texturemanager.hh"

namespace My {
  class MenuState : public GameState {
  public:

    MenuState();

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
      return "MENU";
    }

  private:

    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    TextureManager* _pTextureManager;

    static void s_menuToPlay();
    static void s_exitFromMenu();
  };
}

#endif

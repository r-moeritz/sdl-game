#ifndef PLAYSTATE_HH
#define PLAYSTATE_HH

#include <vector>
#include <memory>
#include "gamestate.hh"
#include "gameobject.hh"
#include "texturemanager.hh"

namespace My {
  class PlayState : public GameState {
  public:

    PlayState();

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
      return "PLAY";
    }

  private:

    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    TextureManager* _pTextureManager;
  };
}

#endif

#ifndef PLAYSTATE_HH
#define PLAYSTATE_HH

#include <vector>
#include <memory>
#include "gamestate.hh"
#include "gameobject.hh"
#include "sdlgameobject.hh"
#include "texturemanager.hh"

namespace MyGame {
  struct PlayState : public GameState {

    PlayState();

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
      return "PLAY";
    }

  private:

    bool collision(std::shared_ptr<SDLGameObject>, std::shared_ptr<SDLGameObject>);

    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    TextureManager* _pTextureManager;
  };
}

#endif

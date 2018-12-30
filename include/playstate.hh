#ifndef PLAYSTATE_HH
#define PLAYSTATE_HH

#include <vector>
#include <memory>
#include "gamestate.hh"
#include "gameobject.hh"
#include "texturemanager.hh"

namespace MyGame {
  struct PlayState : public GameState {

    PlayState();

    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override {
      return "PLAY";
    }

  private:

    bool collision(std::shared_ptr<GameObject>,
                   std::shared_ptr<GameObject>);

    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    TextureManager* _pTextureManager;
  };
}

#endif

#ifndef GAMEOVERSTATE_HH
#define GAMEOVERSTATE_HH

#include <string>
#include <vector>
#include <memory>
#include "gamestate.hh"
#include "gameobject.hh"
#include "texturemanager.hh"
#include "gamestatemachine.hh"
#include "game.hh"

namespace MyGame {
  struct GameOverState : public GameState {

    GameOverState();

    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override {
      return "GAMEOVER";
    }

  private:

    static void s_gameOverToMain();
    static void s_restartPlay();

    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    TextureManager* _pTextureManager;
    Game* _pGame;
  };
}

#endif

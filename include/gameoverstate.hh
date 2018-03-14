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

namespace My {
  class GameOverState : public GameState {
  public:

    GameOverState();

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string stateId() const {
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

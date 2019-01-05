#include "gameoverstate.hh"
#include "menustate.hh"
#include "playstate.hh"
#include "animatedgraphic.hh"
#include "menubutton.hh"
#include "loaderparams.hh"
#include "gameobject.hh"
#include "texturemanager.hh"
#include "gamestatemachine.hh"
#include "game.hh"
#include "SDL2/SDL.h"
#include <vector>

using namespace MyGame;

struct GameOverState::Impl {

  Impl()
    : _pTextureManager(TextureManager::Instance()),
      _pGame(Game::Instance()) {}

  void update() {
    for (auto i = 0; i != _gameObjects.size(); ++i) {
      _gameObjects[i]->update();
    }
  }

  void render() {
    for (auto i = 0; i != _gameObjects.size(); ++i) {
      _gameObjects[i]->draw();
    }
  }

  bool onEnter() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "Entering GAMEOVER state...");

    if (!_pTextureManager->load("assets/gameover.png",
                                "gameovertext",
                                _pGame->renderer())) {
      return false;
    }

    if (!_pTextureManager->load("assets/main.png",
                                "mainbutton",
                                _pGame->renderer())) {
      return false;
    }

    if (!_pTextureManager->load("assets/restart.png",
                                "restartbutton",
                                _pGame->renderer())) {
      return false;
    }

    std::shared_ptr<GameObject> pGameOverText
      = std::make_shared<AnimatedGraphic>(std::make_shared<LoaderParams>(200, 100, 190, 30, "gameovertext"),
                                          2, 2);
    std::shared_ptr<GameObject> pMainButton
      = std::make_shared<MenuButton>(std::make_shared<LoaderParams>(200, 200, 200, 80, "mainbutton"),
                                     s_gameOverToMain);
    std::shared_ptr<GameObject> pRestartButton
      = std::make_shared<MenuButton>(std::make_shared<LoaderParams>(200, 300, 200, 80, "restartbutton"),
                                     s_restartPlay);

    _gameObjects.push_back(pGameOverText);
    _gameObjects.push_back(pMainButton);
    _gameObjects.push_back(pRestartButton);

    return true;
  }

  bool onExit() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "Exiting GAMEOVER state...");

    for (auto i = 0; i != _gameObjects.size(); ++i) {
      _gameObjects[i]->clean();
    }

    _pTextureManager->clearFromTextureMap("gameovertext");
    _pTextureManager->clearFromTextureMap("mainbutton");
    _pTextureManager->clearFromTextureMap("restartbutton");

    return true;
  }

  std::string stateId() const {
    return "GAMEOVER";
  }

private:

  static void s_gameOverToMain();
  static void s_restartPlay();

  std::vector<std::shared_ptr<GameObject>> _gameObjects;
  TextureManager* _pTextureManager;
  Game* _pGame;
};

void GameOverState::Impl::s_gameOverToMain() {
  std::shared_ptr<GameState> pMenuState(new MenuState());
  GameStateMachine::Instance()->changeState(pMenuState);
}

void GameOverState::Impl::s_restartPlay() {
  std::shared_ptr<GameState> pPlayState(new PlayState());
  GameStateMachine::Instance()->changeState(pPlayState);
}

GameOverState::GameOverState()
  : _pImpl(std::make_unique<Impl>()) {}

GameOverState::~GameOverState() = default;
GameOverState::GameOverState(GameOverState&&) = default;
GameOverState& GameOverState::operator=(GameOverState&&) = default;

void GameOverState::update() {
  _pImpl->update();
}

void GameOverState::render() {
  _pImpl->render();
}

bool GameOverState::onEnter() {
  return _pImpl->onEnter();
}

bool GameOverState::onExit() {
  return _pImpl->onExit();
}

std::string GameOverState::stateId() const {
  return _pImpl->stateId();
}

#include "gameoverstate.hh"
#include "menustate.hh"
#include "playstate.hh"
#include "animatedgraphic.hh"
#include "menubutton.hh"
#include "SDL2/SDL.h"

My::GameOverState::GameOverState()
  : _pTextureManager(TextureManager::Instance()),
    _pGame(Game::Instance()) {
}

void My::GameOverState::update() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->update();
  }
}

void My::GameOverState::render() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->draw();
  }
}

bool My::GameOverState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering GAMEOVER state...");

  if (!_pTextureManager->load("assets/gameover.png", "gameovertext",
                              _pGame->renderer())) {
    return false;
  }

  if (!_pTextureManager->load("assets/main.png", "mainbutton",
                              _pGame->renderer())) {
    return false;
  }

  if (!_pTextureManager->load("assets/restart.png", "restartbutton",
                              _pGame->renderer())) {
    return false;
  }

  std::shared_ptr<GameObject> pGameOverText(new AnimatedGraphic(new LoaderParams(200, 100, 190, 30,
                                                                                 "gameovertext"), 2, 2));
  std::shared_ptr<GameObject> pMainButton(new MenuButton(new LoaderParams(200, 200, 200, 80,
                                                                          "mainbutton"), s_gameOverToMain));
  std::shared_ptr<GameObject> pRestartButton(new MenuButton(new LoaderParams(200, 300, 200, 80,
                                                                             "restartbutton"), s_restartPlay));

  _gameObjects.push_back(pGameOverText);
  _gameObjects.push_back(pMainButton);
  _gameObjects.push_back(pRestartButton);

  return true;
}

bool My::GameOverState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting GAMEOVER state...");

  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->clean();
  }

  _pTextureManager->clearFromTextureMap("gameovertext");
  _pTextureManager->clearFromTextureMap("mainbutton");
  _pTextureManager->clearFromTextureMap("restartbutton");

  return true;
}

void My::GameOverState::s_gameOverToMain() {
  std::shared_ptr<GameState> pMenuState(new MenuState());
  GameStateMachine::Instance()->changeState(pMenuState);
}

void My::GameOverState::s_restartPlay() {
  std::shared_ptr<GameState> pPlayState(new PlayState());
  GameStateMachine::Instance()->changeState(pPlayState);
}

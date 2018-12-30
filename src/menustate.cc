#include "menustate.hh"
#include "playstate.hh"
#include "game.hh"
#include "menubutton.hh"
#include "gamestatemachine.hh"
#include "loaderparams.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

MenuState::MenuState()
  : _pTextureManager(TextureManager::Instance()) {}

void MenuState::update() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->update();
  }
}

void MenuState::render() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->draw();
  }
}

bool MenuState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering MENU state...");

  if (!_pTextureManager->load("assets/button.png","playbutton",
                              Game::Instance()->renderer())
      || !_pTextureManager->load("assets/exit.png", "exitbutton",
                                 Game::Instance()->renderer())) {
    return false;
  }

  std::shared_ptr<GameObject> playButton(new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_play));
  std::shared_ptr<GameObject> exitButton(new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exit));

  _gameObjects.push_back(playButton);
  _gameObjects.push_back(exitButton);

  return true;
}

bool MenuState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting MENU state...");

  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->clean();
  }

  _pTextureManager->clearFromTextureMap("playbutton");
  _pTextureManager->clearFromTextureMap("exitbutton");

  return true;
}

void MenuState::s_play() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Play button clicked.");
  std::shared_ptr<GameState> pPlayState(new PlayState());
  GameStateMachine::Instance()->changeState(pPlayState);
}

void MenuState::s_exit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exit button clicked.");
  Game::Instance()->quit();
}

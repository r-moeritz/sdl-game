#include "menustate.hh"
#include "playstate.hh"
#include "SDL2/SDL.h"
#include "game.hh"
#include "menubutton.hh"

My::MenuState::MenuState()
  : _pTextureManager(TextureManager::Instance()) {}

void My::MenuState::update() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->update();
  }
}

void My::MenuState::render() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->draw();
  }
}

bool My::MenuState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering MENU state...");

  if (!_pTextureManager->load("assets/button.png","playbutton",
                              Game::Instance()->renderer())
      || !_pTextureManager->load("assets/exit.png", "exitbutton",
                                 Game::Instance()->renderer())) {
    return false;
  }

  std::shared_ptr<GameObject> button1(new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"),
                                                     s_menuToPlay));
  std::shared_ptr<GameObject> button2(new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"),
                                                     s_exitFromMenu));

  _gameObjects.push_back(button1);
  _gameObjects.push_back(button2);

  return true;
}

bool My::MenuState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting MENU state...");

  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->clean();
  }

  _gameObjects.clear();

  _pTextureManager->clearFromTextureMap("playbutton");
  _pTextureManager->clearFromTextureMap("exitbutton");

  return true;
}

void My::MenuState::s_menuToPlay() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Play button clicked.");
  Game::Instance()->stateMachine()->changeState(new PlayState());
}

void My::MenuState::s_exitFromMenu() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exit button clicked.");
  Game::Instance()->quit();
}

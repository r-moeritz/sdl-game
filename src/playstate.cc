#include "playstate.hh"
#include "SDL2/SDL.h"
#include "game.hh"
#include "player.hh"

My::PlayState::PlayState()
  : _pTextureManager(TextureManager::Instance()) {
}

void My::PlayState::update() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->update();
  }
}

void My::PlayState::render() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->draw();
  }
}

bool My::PlayState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering PLAY state...");

  if (!_pTextureManager->load("assets/helicopter.png", "helicopter", Game::Instance()->renderer())) {
    return false;
  }

  std::shared_ptr<GameObject> player(new Player(new LoaderParams(100, 100, 128, 55, "helicopter")));
  _gameObjects.push_back(player);

  return true;
}

bool My::PlayState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting PLAY state...");

  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->clean();
  }

  _pTextureManager->clearFromTextureMap("helicopter");

  return true;
}

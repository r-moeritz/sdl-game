#include "menustate.hh"
#include "playstate.hh"
#include "menubutton.hh"
#include "gamestatemachine.hh"
#include "loaderparams.hh"
#include "gameobject.hh"
#include "texturemanager.hh"
#include "game.hh"
#include "SDL2/SDL.h"
#include <vector>

using namespace MyGame;

using GameObjectPtr = std::shared_ptr<GameObject>;

struct MenuState::Impl {

  Impl()
    : _pTextureManager(TextureManager::Instance()) {}

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
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering MENU state...");

    if (!_pTextureManager->load("assets/button.png","playbutton", Game::Instance()->renderer())
        || !_pTextureManager->load("assets/exit.png", "exitbutton",
                                   Game::Instance()->renderer())) {
      return false;
    }

    std::shared_ptr<GameObject> playButton
      = std::make_shared<MenuButton>(std::make_shared<LoaderParams>(100, 100, 400, 100, "playbutton"),
                                     s_play);
    std::shared_ptr<GameObject> exitButton
      = std::make_shared<MenuButton>(std::make_shared<LoaderParams>(100, 300, 400, 100, "exitbutton"),
                                     s_exit);

    _gameObjects.push_back(playButton);
    _gameObjects.push_back(exitButton);

    return true;
  }

  bool onExit() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting MENU state...");

    for (auto i = 0; i != _gameObjects.size(); ++i) {
      _gameObjects[i]->clean();
    }

    _pTextureManager->clearFromTextureMap("playbutton");
    _pTextureManager->clearFromTextureMap("exitbutton");

    return true;
  }

  std::string stateId() const {
    return "MENU";
  }

private:

  static void s_play();
  static void s_exit();

  std::vector<GameObjectPtr> _gameObjects;
  TextureManager* _pTextureManager;
};

MenuState::MenuState()
  : _pImpl(std::make_unique<Impl>()) {}

MenuState::~MenuState() = default;
MenuState::MenuState(MenuState&&) = default;
MenuState& MenuState::operator=(MenuState&&) = default;

void MenuState::update() {
  _pImpl->update();
}

void MenuState::render() {
  _pImpl->render();
}

bool MenuState::onEnter() {
  return _pImpl->onEnter();
}

bool MenuState::onExit() {
  return _pImpl->onExit();
}

std::string MenuState::stateId() const {
  return _pImpl->stateId();
}

void MenuState::Impl::s_play() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "Play button clicked.");
  std::shared_ptr<GameState> pPlayState
    = std::make_shared<PlayState>();
  GameStateMachine::Instance()->changeState(pPlayState);
}

void MenuState::Impl::s_exit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "Exit button clicked.");
  Game::Instance()->quit();
}

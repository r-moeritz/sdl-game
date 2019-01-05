#include "menustate.hh"
#include "pausestate.hh"
#include "gamestatemachine.hh"
#include "texturemanager.hh"
#include "menubutton.hh"
#include "game.hh"
#include "loaderparams.hh"
#include "SDL2/SDL.h"
#include <vector>

using namespace MyGame;

using GameObjectPtr = std::shared_ptr<GameObject>;

struct PauseState::Impl {

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
                 "Entering PAUSE state...");

    if (!TextureManager::Instance()->load("assets/resume.png", "resumebutton", Game::Instance()->renderer())) {
      return false;
    }

    if (!TextureManager::Instance()->load("assets/main.png",
                                          "mainbutton",
                                          Game::Instance()->renderer())) {
      return false;
    }

    std::shared_ptr<GameObject> pauseButton
      = std::make_shared<MenuButton>(std::make_shared<LoaderParams>(200, 100, 200, 80, "mainbutton"),
                                   s_main);
    std::shared_ptr<GameObject> resumeButton
      = std::make_shared<MenuButton>(std::make_shared<LoaderParams>(200, 300, 200, 80, "resumebutton"),
                                     s_resume);

    _gameObjects.push_back(pauseButton);
    _gameObjects.push_back(resumeButton);

    return true;
  }

  bool onExit() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "Exiting PAUSE state...");

    for (auto i = 0; i != _gameObjects.size(); ++i) {
      _gameObjects[i]->clean();
    }

    TextureManager::Instance()->clearFromTextureMap("mainbutton");
    TextureManager::Instance()->clearFromTextureMap("resumebutton");

    return true;
  }

  std::string stateId() const {
    return "PAUSE";
  }

private:

  static void s_main();
  static void s_resume();

  std::vector<GameObjectPtr> _gameObjects;
};

PauseState::PauseState()
  : _pImpl(std::make_unique<Impl>()) {}

PauseState::~PauseState() = default;
PauseState::PauseState(PauseState&&) = default;
PauseState& PauseState::operator=(PauseState&&) = default;

void PauseState::update() {
  _pImpl->update();
}

void PauseState::render() {
  _pImpl->render();
}

bool PauseState::onEnter() {
  return _pImpl->onEnter();
}

bool PauseState::onExit() {
  return _pImpl->onExit();
}

std::string PauseState::stateId() const {
  return _pImpl->stateId();
}

void PauseState::Impl::s_main() {
  std::shared_ptr<GameState> pMenuState
    = std::make_shared<MenuState>();
  GameStateMachine::Instance()->changeState(pMenuState);
}

void PauseState::Impl::s_resume() {
  GameStateMachine::Instance()->popState();
}

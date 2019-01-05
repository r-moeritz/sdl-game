#include "playstate.hh"
#include "game.hh"
#include "player.hh"
#include "enemy.hh"
#include "loaderparams.hh"
#include "inputhandler.hh"
#include "gamestatemachine.hh"
#include "pausestate.hh"
#include "gameoverstate.hh"
#include "gameobject.hh"
#include "texturemanager.hh"
#include "SDL2/SDL.h"
#include <vector>

using namespace MyGame;

using GameObjectPtr = std::shared_ptr<GameObject>;

struct PlayState::Impl {

  Impl()
    : _pTextureManager(TextureManager::Instance()) {}

  void update() {
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
      std::shared_ptr<GameState> pPauseState(new PauseState());
      GameStateMachine::Instance()->pushState(pPauseState);
    }

    for (auto i = 0; i != _gameObjects.size(); ++i) {
      _gameObjects[i]->update();
    }

    auto p1 = _gameObjects[0];
    auto p2 = _gameObjects[1];

    if (collision(p1, p2)) {
      std::shared_ptr<GameState> pGameOverState
        = std::make_shared<GameOverState>();
      GameStateMachine::Instance()->pushState(pGameOverState);
    }
  }

  void render() {
    for (auto i = 0; i != _gameObjects.size(); ++i) {
      _gameObjects[i]->draw();
    }
  }

  bool onEnter() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "Entering PLAY state...");

    if (!_pTextureManager->load("assets/helicopter.png", "helicopter", Game::Instance()->renderer())) {
      return false;
    }

    if (!_pTextureManager->load("assets/helicopter2.png", "helicopter2", Game::Instance()->renderer())) {
      return false;
    }

    std::shared_ptr<GameObject> player
      = std::make_shared<Player>(std::make_shared<LoaderParams>(500, 100, 128, 55, "helicopter"),
                                 6);
    std::shared_ptr<GameObject> enemy
      = std::make_shared<Enemy>(std::make_shared<LoaderParams>(100, 100, 128, 55, "helicopter2"),
                                6);

    _gameObjects.push_back(player);
    _gameObjects.push_back(enemy);

    return true;
  }

  bool onExit() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "Exiting PLAY state...");

    for (auto i = 0; i != _gameObjects.size(); ++i) {
      _gameObjects[i]->clean();
    }

    _pTextureManager->clearFromTextureMap("helicopter");

    return true;
  }

  std::string stateId() const {
    return "PLAY";
  }

private:

  bool collision(GameObjectPtr pA, GameObjectPtr pB) {
    // Sides of rect A
    auto leftA = pA->position().x();
    auto rightA = pA->position().x() + pA->width();
    auto topA = pA->position().y();
    auto bottomA = pA->position().y() + pA->height();

    // Sides of rect B
    auto leftB = pB->position().x();
    auto rightB = pB->position().x() + pB->width();
    auto topB = pB->position().y();
    auto bottomB = pB->position().y() + pB->height();

    // Are all of the sides of rect A inside of rect B?
    return (bottomA > topB && topA < bottomB
            && rightA > leftB && leftA < rightB);
  }

  std::vector<GameObjectPtr> _gameObjects;
  TextureManager* _pTextureManager;
};

PlayState::PlayState()
  : _pImpl(std::make_unique<Impl>())  {}

PlayState::~PlayState() = default;
PlayState::PlayState(PlayState&&) = default;
PlayState& PlayState::operator=(PlayState&&) = default;

void PlayState::update() {
  _pImpl->update();
}

void PlayState::render() {
  _pImpl->render();
}

bool PlayState::onEnter() {
  return _pImpl->onEnter();
}

bool PlayState::onExit() {
  return _pImpl->onExit();
}

std::string PlayState::stateId() const {
  return _pImpl->stateId();
}

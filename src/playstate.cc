#include "playstate.hh"
#include "game.hh"
#include "levelparser.hh"
#include "loaderparams.hh"
#include "inputhandler.hh"
#include "gamestatemachine.hh"
#include "pausestate.hh"
#include "gameoverstate.hh"
#include "gameobject.hh"
#include "texturemanager.hh"
#include "level.hh"
#include "SDL2/SDL.h"
#include <vector>

using namespace MyGame;

using GameObjectPtr = std::shared_ptr<GameObject>;
using LevelPtr = std::shared_ptr<Level>;

struct PlayState::Impl {

  Impl()
    : _pTextureManager(TextureManager::Instance()) {}

  void update() {
    // TODO
  }

  void render() {
    _pLevel->render();
  }

  bool onEnter() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "Entering PLAY state...");

    LevelParser lp;
    _pLevel = lp.parseLevel("assets/map1.tmx");

    return true;
  }

  bool onExit() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "Exiting PLAY state...");

    // TODO

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
  LevelPtr _pLevel;
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

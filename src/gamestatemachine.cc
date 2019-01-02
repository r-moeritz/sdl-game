#include "gamestatemachine.hh"
#include "gamestate.hh"
#include "SDL2/SDL.h"
#include <vector>

using namespace MyGame;

struct GameStateMachine::Impl {

  void update() {
    if (!_gameStates.empty()) {
      currentState()->update();
    }
  }

  void render() {
    if (!_gameStates.empty()) {
      currentState()->render();
    }
  }

  void clean() {
    _gameStates.clear();
  }

  void changeState(GameStatePtr pNewState) {
    if (popState()) {
      pushState(pNewState);
    }
  }

  bool pushState(GameStatePtr pNewState) {
    if (!enterState(pNewState)) return false;

    _gameStates.push_back(pNewState);

    return true;
  }

  bool popState() {
    if (_gameStates.empty()) return true;

    if (!exitCurrentState()) return false;;

    _gameStates.pop_back();

    return true;
  }

private:

  std::vector<GameStatePtr> _gameStates;

  GameStatePtr currentState() const {
    return _gameStates.back();
  }

  bool enterState(GameStatePtr pNewState) {
    if (!_gameStates.empty()
        && currentState()->stateId() == pNewState->stateId()) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                   ("Entering " + pNewState->stateId()
                    + " state. Same as current state!").c_str());
      return false;
    }

    auto res = pNewState->onEnter();

    if (!res) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                   ("Entering " + pNewState->stateId()
                    + " state").c_str());
    }

    return res;
  }

  bool exitCurrentState() {
    if (_gameStates.empty()) return true;

    auto res = currentState()->onExit();

    if (!res) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                   ("'Exiting " + currentState()->stateId()
                    + " state").c_str());
    }

    return res;
  }
};

GameStateMachine* GameStateMachine::s_pInstance = nullptr;

GameStateMachine* GameStateMachine::Instance() {
  if (!s_pInstance) {
    s_pInstance = new GameStateMachine();
  }

  return s_pInstance;
}

GameStateMachine::GameStateMachine()
  : _pImpl(std::make_unique<Impl>()) {}

GameStateMachine::~GameStateMachine() = default;
GameStateMachine::GameStateMachine(GameStateMachine&&) = default;
GameStateMachine& GameStateMachine::operator=(GameStateMachine&&) = default;

void GameStateMachine::changeState(GameStatePtr pNewState) {
  _pImpl->changeState(pNewState);
}

bool GameStateMachine::pushState(GameStatePtr pNewState) {
  return _pImpl->pushState(pNewState);
}

bool GameStateMachine::popState() {
  return _pImpl->popState();
}

void GameStateMachine::update() {
  _pImpl->update();
}

void GameStateMachine::render() {
  _pImpl->render();
}

void GameStateMachine::clean() {
  _pImpl->clean();
}

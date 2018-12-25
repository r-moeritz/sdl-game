#include "gamestatemachine.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

GameStateMachine* GameStateMachine::s_pInstance = nullptr;

GameStateMachine* GameStateMachine::Instance() {
  if (!s_pInstance) {
    s_pInstance = new GameStateMachine();
  }

  return s_pInstance;
}

GameStateMachine::GameStateMachine() {

}

void GameStateMachine::changeState(std::shared_ptr<GameState> pNewState) {
  if (popState()) {
    pushState(pNewState);
  }
}

bool GameStateMachine::enterState(std::shared_ptr<GameState> pNewState) {
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

bool GameStateMachine::exitCurrentState() {
  if (_gameStates.empty()) return true;

  auto res = currentState()->onExit();

  if (!res) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 ("'Exiting " + currentState()->stateId()
                  + " state").c_str());
  }

  return res;
}

bool GameStateMachine::pushState(std::shared_ptr<GameState> pNewState) {
  if (!enterState(pNewState)) return false;

  _gameStates.push_back(pNewState);

  return true;
}

bool GameStateMachine::popState() {
  if (_gameStates.empty()) return true;

  if (!exitCurrentState()) return false;;

  _gameStates.pop_back();

  return true;
}

std::shared_ptr<GameState> GameStateMachine::currentState() const {
  return _gameStates.back();
}

void GameStateMachine::update() {
  if (!_gameStates.empty()) {
    currentState()->update();
  }
}

void GameStateMachine::render() {
  if (!_gameStates.empty()) {
    currentState()->render();
  }
}

void GameStateMachine::clean() {
  _gameStates.clear();
}

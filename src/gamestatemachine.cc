#include "gamestatemachine.hh"
#include "SDL2/SDL.h"

My::GameStateMachine* My::GameStateMachine::s_pInstance = nullptr;

My::GameStateMachine* My::GameStateMachine::Instance() {
  if (!s_pInstance) {
    s_pInstance = new GameStateMachine();
  }

  return s_pInstance;
}

My::GameStateMachine::GameStateMachine() {

}

void My::GameStateMachine::changeState(std::shared_ptr<GameState> pNewState) {
  if (!exitCurrentState()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 ("'Exiting " + currentState()->stateId()
                  + " state").c_str());
    return;
  }

  if (!enterState(pNewState)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 ("Entering " + pNewState->stateId()
                  + " state").c_str());
    return;
  }

  popState();
  pushState(pNewState);
}

bool My::GameStateMachine::enterState(std::shared_ptr<GameState> pNewState) {
  if (!_gameStates.empty()
      && currentState()->stateId() == pNewState->stateId()) return false;

  return pNewState->onEnter();
}

bool My::GameStateMachine::exitCurrentState() {
  if (_gameStates.empty()) return true;

  return currentState()->onExit();
}

void My::GameStateMachine::pushState(std::shared_ptr<GameState> pNewState) {
  _gameStates.push_back(pNewState);
}

void My::GameStateMachine::popState() {
  if (!_gameStates.empty()) {
    _gameStates.pop_back();
  }
}

std::shared_ptr<My::GameState> My::GameStateMachine::currentState() const {
  return _gameStates.back();
}

void My::GameStateMachine::update() {
  if (!_gameStates.empty()) {
    currentState()->update();
  }
}

void My::GameStateMachine::render() {
  if (!_gameStates.empty()) {
    currentState()->render();
  }
}

void My::GameStateMachine::clean() {
  _gameStates.clear();
}

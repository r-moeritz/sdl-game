#include "gamestatemachine.hh"

void My::GameStateMachine::pushState(My::GameState* pNewState) {
  std::shared_ptr<GameState> pState(pNewState);
  _gameStates.push_back(pState);
  pState->onEnter();
}

void My::GameStateMachine::changeState(My::GameState* pNewState) {
  if (_gameStates.empty()) return;

  auto pCurrentState = currentState();
  if (pCurrentState->stateId() == pNewState->stateId()) return;

  if (pCurrentState->onExit()) {
    _gameStates.pop_back();
  }

  std::shared_ptr<GameState> pState(pNewState);
  _gameStates.push_back(pState);
  pState->onEnter();
}

void My::GameStateMachine::popState() {
  if (_gameStates.empty()) return;

  auto pCurrentState = currentState();
  if (pCurrentState->onExit()) {
    _gameStates.pop_back();
  }
}

std::shared_ptr<My::GameState> My::GameStateMachine::currentState() const {
  return _gameStates.back();
}

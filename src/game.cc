#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "game.hh"
#include "menustate.hh"
#include "playstate.hh"
#include <memory>

using namespace MyGame;

Game* Game::s_pInstance = nullptr;

Game* Game::Instance() {
  if (!s_pInstance) {
    s_pInstance = new Game();
  }

  return s_pInstance;
}

Game::Game()
  : _pInputHandler(InputHandler::Instance()),
    _pGameStateMachine(GameStateMachine::Instance()) {

}

bool Game::init(const char* title, int xpos, int ypos,
                int height, int width, bool fullscreen) {
  /*
   * Conditionally compile SDL_Init and ÍMG_Init, because they
   * aren't necessary (and don't work) on Android.
   */
#ifndef ANDROID
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  int imgFlags = IMG_INIT_PNG;
  if (!( IMG_Init( imgFlags ) & imgFlags )) {
    return false;
  }
#endif

  int flags = SDL_WINDOW_SHOWN;
  if (fullscreen) {
    flags |= SDL_WINDOW_FULLSCREEN;
  }

  _pWindow = SDL_CreateWindow(title, xpos, ypos,
                              height, width, flags);
  if (!_pWindow) {
    return false;
  }

  _pRenderer = SDL_CreateRenderer(_pWindow, -1, 0);
  if (!_pRenderer) {
    return false;
  }

  _pInputHandler->initializeJoysticks();

  std::shared_ptr<GameState> pMenuState(new MenuState());
  _pGameStateMachine->changeState(pMenuState);

  _running = true;
  return _running;
}

void Game::handleEvents() {
  _pInputHandler->update();
}

void Game::render() {
  SDL_RenderClear(_pRenderer);

  _pGameStateMachine->render();

  SDL_RenderPresent(_pRenderer);
}

void Game::update() {
  _pGameStateMachine->update();
}

void Game::clean() {
  _pGameStateMachine->clean();
  _pInputHandler->clean();

  SDL_DestroyWindow(_pWindow);
  SDL_DestroyRenderer(_pRenderer);
}

void Game::quit() {
  _running = false;
}

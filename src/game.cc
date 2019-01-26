#include "game.hh"
#include "menustate.hh"
#include "playstate.hh"
#include "inputhandler.hh"
#include "gamestatemachine.hh"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace MyGame;

struct Game::Impl {

  Impl()
    : _pInputHandler(InputHandler::Instance()),
      _pGameStateMachine(GameStateMachine::Instance()) {}

  bool init(const char* title,
            int xpos,
            int ypos,
            int width,
            int height,
            bool fullscreen) {
    // Don't call SDL_Init and ÍMG_Init on Android,
    // because they aren't necessary (and don't work).
#ifndef ANDROID
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      return false;
    }

    _width = width;
    _height = height;

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
                                width, height, flags);
    if (!_pWindow) {
      return false;
    }

    _pRenderer = SDL_CreateRenderer(_pWindow, -1, 0);
    if (!_pRenderer) {
      return false;
    }

    _pInputHandler->initializeJoysticks();

    std::shared_ptr<GameState> pMenuState
      = std::make_shared<MenuState>();
    _pGameStateMachine->changeState(pMenuState);

    _running = true;
    return _running;
  }

  void render() {
    SDL_RenderClear(_pRenderer);

    _pGameStateMachine->render();

    SDL_RenderPresent(_pRenderer);
  }

  void clean() {
    _pGameStateMachine->clean();
    _pInputHandler->clean();

    SDL_DestroyWindow(_pWindow);
    SDL_DestroyRenderer(_pRenderer);
  }

  void update() {
    _pGameStateMachine->update();
  }

  void handleEvents() {
    _pInputHandler->update();
  }

  void quit() {
    _running = false;
  }

  int width() const {
    return _width;
  }

  int height() const {
    return _height;
  }

  bool running() const {
    return _running;
  }

  SDL_Renderer* renderer() const {
    return _pRenderer;
  }

private:

  int _width;
  int _height;
  bool _running;

  // Owned by SDL
  SDL_Window* _pWindow;
  SDL_Renderer* _pRenderer;

  InputHandler* _pInputHandler;
  GameStateMachine* _pGameStateMachine;
};

Game* Game::s_pInstance = nullptr;

Game* Game::Instance() {
  if (!s_pInstance) {
    s_pInstance = new Game();
  }

  return s_pInstance;
}

Game::Game()
  : _pImpl(std::make_unique<Impl>()) {}

Game::~Game() = default;
Game::Game(Game&&) = default;
Game& Game::operator=(Game&&) = default;

bool Game::init(const char* title, int xpos, int ypos,
                int width, int height, bool fullscreen) {
  return _pImpl->init(title, xpos, ypos, width, height,
                      fullscreen);
}

void Game::handleEvents() {
  _pImpl->handleEvents();
}

void Game::render() {
  _pImpl->render();
}

void Game::update() {
  _pImpl->update();
}

void Game::clean() {
  _pImpl->clean();
}

void Game::quit() {
  _pImpl->quit();
}

int Game::width() const {
  return _pImpl->width();
}

int Game::height() const {
  return _pImpl->height();
}

bool Game::running() const {
  return _pImpl->running();
}

SDL_Renderer* Game::renderer() const {
  return _pImpl->renderer();
}

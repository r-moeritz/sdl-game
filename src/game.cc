#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "game.hh"
#include "inputhandler.hh"
#include "menustate.hh"
#include "playerstate.hh"

My::Game* My::Game::s_pInstance = nullptr;

My::Game* My::Game::Instance() {
    if (!s_pInstance) {
        s_pInstance = new My::Game();
    }

    return s_pInstance;
}

My::Game::Game()
    : _pInputHandler(My::InputHandler::Instance()) {}

bool My::Game::init(const char* title, int xpos, int ypos,
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
    _pGameStateMachine->pushState(new MenuState());

    _running = true;
    return _running;
}

void My::Game::handleEvents() {
    _pInputHandler->update();

    if (_pInputHandler->isKeyDown(SDL_SCANCODE_SPACE)) {
        _pGameStateMachine->changeState(new PlayerState());
    }
}

void My::Game::render() {
    SDL_RenderClear(_pRenderer);

    _pGameStateMachine->render();

    SDL_RenderPresent(_pRenderer);
}

void My::Game::update() {
    _pGameStateMachine->update();
}

void My::Game::clean() {
    _pGameStateMachine->popState();
    _pInputHandler->clean();

    SDL_DestroyWindow(_pWindow);
    SDL_DestroyRenderer(_pRenderer);
}

void My::Game::quit() {
    _running = false;
}

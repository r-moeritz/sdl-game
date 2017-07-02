#include "game.hh"
#include "SDL2/SDL.h"
#include <iostream>

using namespace std;

bool My::Game::init(const char* title, int xpos, int ypos,
        int height, int width, bool fullscreen) {
    /* SDL_Init() doesn't seem to work (or be necessary) on Android
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cerr << "ERROR SDL_Init" << endl;
        return false;        
    }
    */
    
    int flags = SDL_WINDOW_SHOWN;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    
    _pWindow = SDL_CreateWindow(title, xpos, ypos,
            height, width, flags);        
    if (!_pWindow) {
        cerr << "ERROR SDL_CreateWindow" << endl;
        return false;
    }
            
    _pRenderer = SDL_CreateRenderer(_pWindow, -1, 0);
    if (!_pRenderer) {
        cerr << "ERROR SDL_CreateRenderer" << endl;
        return false;
    }
        
    SDL_SetRenderDrawColor(_pRenderer, 255, 0, 0, 255);

    _pTextureMgr->load("assets/animate-alpha.png", "animate", _pRenderer);
    _player.load(300, 300, 128, 82, "animate");

    _running = true;    
    return _running;
}

void My::Game::handleEvents() {
    SDL_Event event;
    if (!SDL_PollEvent(&event)) return;
    
    switch (event.type) {
        case SDL_QUIT:
            _running = false;
            break;
    }
}

void My::Game::render() {
    SDL_RenderClear(_pRenderer);

    _player.draw(_pRenderer);
                    
    SDL_RenderPresent(_pRenderer);
}

void My::Game::update() {
    _player.update();
}

void My::Game::clean() {
    _player.clean();    

    SDL_DestroyWindow(_pWindow);
    SDL_DestroyRenderer(_pRenderer);
    SDL_Quit();
    
    _pWindow = nullptr;
    _pRenderer = nullptr;
}
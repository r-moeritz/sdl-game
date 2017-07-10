#include "enemy.hh"
#include "player.hh"
#include "game.hh"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

My::Game* My::Game::s_pInstance = nullptr;

My::Game* My::Game::Instance() {
    if (!s_pInstance) {
        s_pInstance = new My::Game();
    }
    
    return s_pInstance;
}

My::Game::Game() : _pTextureMgr(My::TextureManager::Instance()) {}

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
        
    SDL_SetRenderDrawColor(_pRenderer, 255, 0, 0, 255);

    _pTextureMgr->load("assets/animate-alpha.png", "animate", _pRenderer);
    
    _gameObjects.push_back(new My::Player(
            new My::LoaderParams(100, 100, 128, 82, "animate"))); 
    _gameObjects.push_back(new My::Enemy(
            new My::LoaderParams(300, 300, 128, 82, "animate")));
        
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

    for (std::vector<My::GameObject*>::size_type i = 0;
            i != _gameObjects.size(); ++i) {
        _gameObjects[i]->draw();
    }
                    
    SDL_RenderPresent(_pRenderer);
}

void My::Game::update() {
    for (std::vector<My::GameObject*>::size_type i = 0;
            i != _gameObjects.size(); ++i) {
        _gameObjects[i]->update();
    }
}

void My::Game::clean() {
    for (std::vector<My::GameObject*>::size_type i = 0;
            i != _gameObjects.size(); ++i) {
        _gameObjects[i]->clean();
    }
    
    // TODO delete gameobjects and remove from collection?

    SDL_DestroyWindow(_pWindow);
    SDL_DestroyRenderer(_pRenderer);
    SDL_Quit();
    
    _pWindow = nullptr;
    _pRenderer = nullptr;
}
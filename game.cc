#include "enemy.hh"
#include "player.hh"
#include "game.hh"
#include "SDL2/SDL.h"
#include <iostream>

My::Game* My::Game::s_pInstance = nullptr;

My::Game* My::Game::Instance() {
    if (!s_pInstance) {
        s_pInstance = new My::Game();
    }
    
    return s_pInstance;
}

bool My::Game::init(const char* title, int xpos, int ypos,
        int height, int width, bool fullscreen) {
    /* SDL_Init() doesn't seem to work (or be necessary) on Android
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "ERROR SDL_Init" << std::endl;
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
        std::cerr << "ERROR SDL_CreateWindow" << std::endl;
        return false;
    }
            
    _pRenderer = SDL_CreateRenderer(_pWindow, -1, 0);
    if (!_pRenderer) {
        std::cerr << "ERROR SDL_CreateRenderer" << std::endl;
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
#include "SDL2/SDL.h"
#include "game.hh"

int main(int argc, char* argv[]) {
    My::Game* game = My::Game::Instance();
    
    game->init("chapter 1", 100, 100, 640, 480, false);
    
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
        
        SDL_Delay(10);        
    }
    
    game->clean();
    
    return 0;
}
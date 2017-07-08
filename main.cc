#include "SDL2/SDL.h"
#include "game.hh"

int main(int argc, char* argv[]) {

    #ifdef DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    #endif

    My::Game* game = My::Game::Instance();
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Initializing game...");
    game->init("chapter 1", 100, 100, 640, 480, false);
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering game loop...");
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
        
        SDL_Delay(10);
    }
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Cleaning up...");
    game->clean();
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting...");
    return 0;
}

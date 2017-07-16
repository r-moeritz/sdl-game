#include "game.hh"
#include "SDL2/SDL.h"

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

int main(int argc, char* argv[]) {

    #ifdef DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    #endif

    My::Game* game = My::Game::Instance();
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Initializing game...");
    game->init("chapter 1", 100, 100, 640, 480, false);

    int frameStart, frameTime;
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering game loop...");
    while (game->running()) {
      frameStart = SDL_GetTicks();
      
      game->handleEvents();
      game->update();
      game->render();

      frameTime = SDL_GetTicks() - frameStart;

      if (frameTime < DELAY_TIME) {	
	SDL_Delay(int(DELAY_TIME - frameTime));
      }
    }
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Cleaning up...");
    game->clean();
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting...");
    return 0;
}

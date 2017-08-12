#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "SDL2/SDL.h"
#include "inputhandler.hh"
#include "gamestatemachine.hh"

namespace My {
        class Game {
        public:
                bool init(const char* title, int xpos, int ypos,
                          int height, int width, bool fullscreen);
                void render();
                void clean();
                void update();
                void handleEvents();
                void quit();

                inline bool running() const { return _running; }
                inline SDL_Renderer* renderer() const { return _pRenderer; }
                inline GameStateMachine* stateMachine() const { return _pGameStateMachine; }

                static Game* Instance();

        private:

                Game();

                bool _running;

                // Owned by SDL
                SDL_Window* _pWindow;
                SDL_Renderer* _pRenderer;

                // Need to be manually deleted
                InputHandler* _pInputHandler;
                GameStateMachine* _pGameStateMachine = new GameStateMachine();

                static Game* s_pInstance;
        };
}

#endif

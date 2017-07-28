#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "texturemanager.hh"
#include "gameobject.hh"
#include "inputhandler.hh"
#include "SDL2/SDL.h"

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

                static Game* Instance();

        private:

                Game();

                SDL_Window* _pWindow;
                SDL_Renderer* _pRenderer;

                bool _running;

                InputHandler* _pInputHandler;
                TextureManager* _pTextureMgr;

                std::vector<GameObject*> _gameObjects;

                static Game* s_pInstance;
        };
}

#endif

#ifndef GAME_HH
#define GAME_HH

#include "SDL2/SDL.h"
#include "texturemanager.hh"
#include "player.hh"

namespace My {
    class Game {
        public:
                    
        bool init(const char* title, int xpos, int ypos,
            int height, int width, bool fullscreen);
        void render();
        void clean();
        void update();
        void handleEvents();
        
        bool running() const { return _running; }
        
        private:
        
        SDL_Window* _pWindow;
        SDL_Renderer* _pRenderer;
               
        bool _running;

        My::TextureManager* _pTextureMgr = My::TextureManager::Instance();
        My::Player _player;
    };
}

#endif
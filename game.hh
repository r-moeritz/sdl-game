#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "SDL2/SDL.h"
#include "texturemanager.hh"
#include "gameobject.hh"

namespace My {
    class Game {
        public:
                    
        bool init(const char* title, int xpos, int ypos,
            int height, int width, bool fullscreen);
        void render();
        void clean();
        void update();
        void handleEvents();
                
        inline bool running() const { return _running; }
        inline SDL_Renderer* renderer() const { return _pRenderer; }
        
        static My::Game* Instance();
        
        private:

        Game();
                
        SDL_Window* _pWindow;
        SDL_Renderer* _pRenderer;
               
        bool _running;

        My::TextureManager* _pTextureMgr;
        std::vector<My::GameObject*> _gameObjects;
        
        static My::Game* s_pInstance;      
    };
}

#endif

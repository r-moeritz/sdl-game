#ifndef TEXTUREMANAGER_HH
#define TEXTUREMANAGER_HH

#include <string>
#include <map>
#include "SDL2/SDL.h"

namespace My {
    class TextureManager {
        public:
        
        bool load(std::string fileName, std::string id, 
            SDL_Renderer* pRenderer);
        void draw(std::string id, int x, int y, int width, int height,
            SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void drawFrame(std::string id, int x, int y, int width, int height,
            int currentRow, int currentFrame, SDL_Renderer* pRenderer, 
            SDL_RendererFlip flip = SDL_FLIP_NONE);

        static TextureManager* Instance();
                        
        private:

        TextureManager() {}
                
        std::map<std::string, SDL_Texture*> _textureMap;
        
        static TextureManager* s_pInstance;
    };
}

#endif

#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include "texturemanager.hh"
#include "SDL2/SDL.h"

namespace My {
    class GameObject {
        public:
        
        virtual void load(int x, int y, int width, int height, 
            std::string textureId);
        virtual void draw(SDL_Renderer*);
        virtual void update();
        virtual void clean() = 0;
        
        protected:

        My::TextureManager* _pTextureMgr = My::TextureManager::Instance();
        std::string _textureId;
        
        int _currentFrame;
        int _currentRow;

        int _x;
        int _y;
        
        int _width;
        int _height;
    };
}

#endif
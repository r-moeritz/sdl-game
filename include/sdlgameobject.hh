#ifndef SDLGAMEOBJECT_HH
#define SDLGAMEOBJECT_HH

#include <string>
#include "gameobject.hh"
#include "loaderparams.hh"
#include "texturemanager.hh"
#include "game.hh"
#include "SDL2/SDL.h"

namespace My {
    class SDLGameObject : public GameObject {
        public:

        virtual void draw();
        virtual void update() = 0;
        virtual void clean() = 0;
        
        protected:

        SDLGameObject(const LoaderParams*);
        virtual ~SDLGameObject() {}
        
        int _x, _y, _width, _height;
        std::string _textureId;
        
        int _curRow = 0;
        int _curFrame = 0;
        
        TextureManager* _pTextureMgr;
        Game* _pGame;
    };
}

#endif

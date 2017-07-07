#ifndef SDLGAMEOBJECT_HH
#define SDLGAMEOBJECT_HH

#include <string>
#include "gameobject.hh"
#include "loaderparams.hh"
#include "texturemanager.hh"
#include "game.hh"

namespace My {
    class SDLGameObject : public GameObject {
        public:
        
        SDLGameObject(const My::LoaderParams*);
        
        virtual void draw();
        virtual void update();
        virtual void clean();
        
        protected:
        
        int _x, _y, _width, _height;
        std::string _textureId;
        
        int _curRow = 1;
        int _curFrame = 1;
        
        My::TextureManager* _pTextureMgr;
        My::Game* _pGame;
    };
}

#endif
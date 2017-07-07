#ifndef ENEMY_HH
#define ENEMY_HH

#include "sdlgameobject.hh"
#include "loaderparams.hh"

namespace My {
    class Enemy : public My::SDLGameObject {
        public:
        
        Enemy(const My::LoaderParams*); 
        
        virtual void update();
    };
}

#endif
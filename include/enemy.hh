#ifndef ENEMY_HH
#define ENEMY_HH

#include "sdlgameobject.hh"
#include "loaderparams.hh"

namespace My {
    class Enemy : public SDLGameObject {
        public:
        
        Enemy(const LoaderParams*); 
        
        virtual void update();
        virtual void clean();
    };
}

#endif

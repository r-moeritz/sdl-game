#ifndef PLAYER_HH
#define PLAYER_HH

#include "sdlgameobject.hh"
#include "loaderparams.hh"

namespace My {
    class Player : public My::SDLGameObject {
        public:
        
        Player(const My::LoaderParams*);
        
        virtual void update();
        virtual void clean();
    };
}

#endif

#ifndef PLAYER_HH
#define PLAYER_HH

#include "sdlgameobject.hh"
#include "loaderparams.hh"
#include "inputhandler.hh"

namespace My {
    class Player : public SDLGameObject {
    public:

        Player(const LoaderParams*);
        
        virtual void update();
        virtual void clean();

    private:

        void handleInput();
        InputHandler* _pInputHandler;
    };
}

#endif

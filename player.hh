#ifndef PLAYER_HH
#define PLAYER_HH

#include "gameobject.hh"

namespace My {
    class Player : public My::GameObject {
        public:
        
        Player() {}
        
        void update();
        void clean();
    };
}

#endif
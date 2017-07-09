#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include "loaderparams.hh"

namespace My {
    class GameObject {
        public:
        
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean() = 0;
        
        protected:

        GameObject(const My::LoaderParams*) {}
        virtual ~GameObject() {}
    };
}

#endif
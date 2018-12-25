#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include "loaderparams.hh"

namespace MyGame {
  struct GameObject {

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
        
  protected:

    GameObject(const LoaderParams*) {}
    virtual ~GameObject() {}
  };
}

#endif

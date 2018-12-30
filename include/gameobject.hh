#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include "vector2d.hh"

namespace MyGame {
  struct GameObject {

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    virtual Vector2D position() const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;
  };
}

#endif

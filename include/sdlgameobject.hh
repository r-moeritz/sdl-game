#ifndef SDLGAMEOBJECT_HH
#define SDLGAMEOBJECT_HH

#include "gameobject.hh"
#include "vector2d.hh"
#include <memory>

namespace MyGame {
  struct LoaderParams;

  struct SDLGameObject : public GameObject {

    ~SDLGameObject();
    SDLGameObject(SDLGameObject&&);
    SDLGameObject& operator=(SDLGameObject&&);

    void draw() override;
    void update() override;
    virtual void clean() = 0;

    Vector2D position() const override;
    int width() const override;
    int height() const override;

  protected:

    SDLGameObject(const LoaderParams*);

    Vector2D& velocity();
    void velocity(Vector2D const&);

    Vector2D& acceleration();
    void acceleration(Vector2D const&);

    int currentFrame() const;
    void currentFrame(int);

  private:

    struct Impl;
    std::unique_ptr<Impl> _pImpl;
  };
}

#endif

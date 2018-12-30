#ifndef ANIMATEDGRAPHIC_HH
#define ANIMATEDGRAPHIC_HH

#include "gameobject.hh"
#include <memory>

namespace MyGame {
  struct LoaderParams;

  struct AnimatedGraphic : public GameObject {

    AnimatedGraphic(const LoaderParams*, int, int);
    ~AnimatedGraphic();
    AnimatedGraphic(AnimatedGraphic&&);
    AnimatedGraphic& operator=(AnimatedGraphic&&);

    void draw() override;
    void update() override;
    void clean() override;

    Vector2D position() const override;
    int width() const override;
    int height() const override;

  private:

    struct Impl;
    std::unique_ptr<Impl> _pImpl;
  };
}

#endif

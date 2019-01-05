#ifndef ENEMY_HH
#define ENEMY_HH

#include "gameobject.hh"
#include <memory>

namespace MyGame {
  struct LoaderParams;

  struct Enemy : public GameObject {

    Enemy(std::shared_ptr<LoaderParams>, int);
    ~Enemy();
    Enemy(Enemy&&);
    Enemy& operator=(Enemy&&);

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

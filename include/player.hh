#ifndef PLAYER_HH
#define PLAYER_HH

#include "gameobject.hh"
#include <memory>

namespace MyGame {
  struct LoaderParams;

  struct Player : public GameObject {

    Player(std::shared_ptr<LoaderParams>, int);
    ~Player();
    Player(Player&&);
    Player& operator=(Player&&);

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

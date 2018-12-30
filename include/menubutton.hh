#ifndef MENUBUTTON_HH
#define MENUBUTTON_HH

#include "gameobject.hh"
#include <functional>
#include <memory>

namespace MyGame {
  struct LoaderParams;

  struct MenuButton : public GameObject {

    MenuButton(const LoaderParams*,
               std::function<void()>);
    ~MenuButton();
    MenuButton(MenuButton&&);
    MenuButton& operator=(MenuButton&&);

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

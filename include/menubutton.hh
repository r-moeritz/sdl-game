#ifndef MENUBUTTON_HH
#define MENUBUTTON_HH

#include "sdlgameobject.hh"
#include "loaderparams.hh"

namespace My {
  class MenuButton : public SDLGameObject {
  public:
    MenuButton(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

  private:
    enum class ButtonState { mouseOut, mouseOver, clicked };
  };
}

#endif

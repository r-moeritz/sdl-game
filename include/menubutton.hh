#ifndef MENUBUTTON_HH
#define MENUBUTTON_HH

#include <functional>
#include "sdlgameobject.hh"
#include "loaderparams.hh"

namespace My {
  class MenuButton : public SDLGameObject {
  public:

    MenuButton(const LoaderParams* pParams, std::function<void()> callback);

    virtual void draw();
    virtual void update();
    virtual void clean();

  private:

    enum class ButtonState { mouseOut, mouseOver, clicked };
    std::function<void()> _callback;
    bool _released;

    void menuToPlay();
    void exitFromMenu();
  };
}

#endif

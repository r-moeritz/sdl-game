#ifndef INPUTHANDLER_HH
#define INPUTHANDLER_HH

#include "vector2d.hh"
#include "SDL2/SDL.h"
#include <memory>

namespace MyGame {
  enum class MouseButton { left, middle, right };

  struct InputHandler {

    ~InputHandler();
    InputHandler(InputHandler&&);
    InputHandler& operator=(InputHandler&&);

    static InputHandler* Instance();

    void update();
    void clean();

    int x(int joy, int stick) const;
    int y(int joy, int stick) const;

    bool buttonState(int joy, int buttonNr) const;
    bool isKeyDown(SDL_Scancode key) const;
    bool mouseButtonState(MouseButton) const;
    Vector2D mousePosition() const;

    void initializeJoysticks();
    bool joysticksInitialized();

  private:
    InputHandler();

    struct Impl;
    std::unique_ptr<Impl> _pImpl;

    static InputHandler* s_pInstance;
  };
}

#endif // INPUTHANDLER_HH

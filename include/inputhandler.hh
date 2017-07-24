#ifndef INPUTHANDLER_HH
#define INPUTHANDLER_HH

#include "vector2d.hh"
#include "SDL2/SDL.h"
#include <vector>
#include <utility>

namespace My {
  class InputHandler {
  public:
    static InputHandler* Instance();

    void update();
    void clean();

    int x(int joy, int stick) const;
    int y(int joy, int stick) const;

    void initializeJoysticks();
    inline bool joysticksInititalized() {
      return _joysticksInitialized;
    }

  private:
    InputHandler() {}
    ~InputHandler() {}

    static InputHandler* s_pInstance;

    std::vector<std::pair<Vector2D*, Vector2D*>> _joystickValues;
    std::vector<SDL_Joystick*> _joysticks;
    bool _joysticksInitialized;
  };
}

#endif // INPUTHANDLER_HH

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

    bool buttonState(int joy, int buttonNr) const;

    void initializeJoysticks();
    inline bool joysticksInitialized() {
      return _joysticksInitialized;
    }

  private:
    InputHandler() {}
    ~InputHandler() {}

    static InputHandler* s_pInstance;

    std::vector<std::pair<Vector2D*, Vector2D*>> _joystickValues;
    std::vector<SDL_Joystick*> _joysticks;
    std::vector<std::vector<bool>> _buttonStates;
    bool _joysticksInitialized;
    int _joystickDeadzone = 10000;
  };
}

#endif // INPUTHANDLER_HH

#ifndef INPUTHANDLER_HH
#define INPUTHANDLER_HH

#include "vector2d.hh"
#include "SDL2/SDL.h"
#include <vector>
#include <utility>

namespace My {
  enum class MouseButton { left, middle, right };

  class InputHandler {
  public:
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
    inline bool joysticksInitialized() {
      return _joysticksInitialized;
    }

  private:
    InputHandler();
    ~InputHandler() {}

    void onJoystickAxisMove(const SDL_Event& event);
    void onJoystickButtonUpOrDown(const SDL_Event& event);
    void onKeyUpOrDown();
    void onMouseButtonUpOrDown(const SDL_Event&);
    void onMouseMove(const SDL_Event&);

    static InputHandler* s_pInstance;

    std::vector<std::pair<Vector2D*, Vector2D*>> _joystickValues;
    std::vector<SDL_Joystick*> _joysticks;
    std::vector<std::vector<bool>> _buttonStates;
    std::vector<bool> _mouseButtonStates;
    Vector2D _mousePos;
    bool _joysticksInitialized;
    int _joystickDeadzone = 10000;
    const Uint8* _keyState = nullptr;
  };
}

#endif // INPUTHANDLER_HH

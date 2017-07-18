#ifndef INPUTHANDLER_HH
#define INPUTHANDLER_HH

#include "SDL2/SDL.h"
#include <vector>

namespace My {
  class InputHandler {
  public:
    static InputHandler* Instance();

    void update();
    void clean();

    void initializeJoysticks();
    inline bool joysticksInititalized() {
      return _joysticksInitialized;
    }

  private:
    InputHandler() {}
    ~InputHandler() {}

    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> _joysticks;
    bool _joysticksInitialized;
  };
}

#endif // INPUTHANDLER_HH

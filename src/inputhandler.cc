#include "inputhandler.hh"
#include "game.hh"
#include <string>
#include <vector>
#include <utility>

using namespace MyGame;

struct InputHandler::Impl {

  Impl()
    : _mousePos(0, 0) {
    for (auto i = 0; i != 3; ++i) {
      _mouseButtonStates.push_back(false);
    }
  }

  void update() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        Game::Instance()->quit();
        break;

      case SDL_JOYAXISMOTION:
        onJoystickAxisMove(event);
        break;

      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        onJoystickButtonUpOrDown(event);
        break;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        onKeyUpOrDown();
        break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        onMouseButtonUpOrDown(event);
        break;

      case SDL_MOUSEMOTION:
        onMouseMove(event);
        break;
      }
    }
  }

  void clean() {
    if (!_joysticksInitialized) return;

    for (auto i = 0; i != SDL_NumJoysticks(); ++i) {
      SDL_JoystickClose(_joysticks[i]);
    }
  }

  int x(int joy, int stick) const {
    if (!_joystickValues.size()) return 0;

    if (stick == 1) {
      return _joystickValues[joy].first->x();
    }
    else if (stick == 2) {
      return _joystickValues[joy].second->x();
    }

    return 0;
  }

  int y(int joy, int stick) const {
    if (!_joystickValues.size()) return 0;

    if (stick == 1) {
      return _joystickValues[joy].first->y();
    }
    else if (stick == 2) {
      return _joystickValues[joy].second->y();
    }

    return 0;
  }

  bool buttonState(int joy, int buttonNr) const {
    return _buttonStates[joy][buttonNr];
  }

  bool isKeyDown(SDL_Scancode key) const {
    if (!_keyState) return false;

    return _keyState[key];
  }

  bool mouseButtonState(MouseButton button) const {
    auto i = static_cast<int>(button);
    return _mouseButtonStates[i];
  }

  Vector2D mousePosition() const {
    return _mousePos;
  }

  void initializeJoysticks() {
    if (!SDL_WasInit(SDL_INIT_JOYSTICK)) {
      SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if (SDL_NumJoysticks() > 0) {
      for (auto i = 0; i != SDL_NumJoysticks(); ++i) {
        SDL_Joystick* joy = SDL_JoystickOpen(i);

        if (joy) {
          _joysticks.push_back(joy);
          _joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));

          std::vector<bool> buttons;
          for (int k = 0; k != SDL_JoystickNumButtons(joy); ++k) {
            buttons.push_back(false);
          }
          _buttonStates.push_back(buttons);
        }
        else {
          SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        }
      }

      SDL_JoystickEventState(SDL_ENABLE);
      _joysticksInitialized = true;

      SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                   ("Initialized " + std::to_string(_joysticks.size()) + " joystick(s)").c_str());
    }
    else {
      _joysticksInitialized = false;
    }
  }

  bool joysticksInitialized() {
    return _joysticksInitialized;
  }

private:

  void onJoystickAxisMove(const SDL_Event& event) {
    auto whichOne = event.jaxis.which;

    // Move left stick left or right
    if (event.jaxis.axis == 0) {
      if (event.jaxis.value > _joystickDeadzone) {
        _joystickValues[whichOne].first->setX(1);
      }
      else if (event.jaxis.value < -_joystickDeadzone) {
        _joystickValues[whichOne].first->setX(-1);
      }
      else {
        _joystickValues[whichOne].first->setX(0);
      }
    }

    // Move left stick up or down
    if (event.jaxis.axis == 1) {
      if (event.jaxis.value > _joystickDeadzone) {
        _joystickValues[whichOne].first->setY(1);
      }
      else if (event.jaxis.value < -_joystickDeadzone) {
        _joystickValues[whichOne].first->setY(-1);
      }
      else {
        _joystickValues[whichOne].first->setY(0);
      }
    }

    // Move right stick left or right
    if (event.jaxis.axis == 3) {
      if (event.jaxis.value > _joystickDeadzone) {
        _joystickValues[whichOne].second->setX(1);
      }
      else if (event.jaxis.value < -_joystickDeadzone) {
        _joystickValues[whichOne].second->setX(-1);
      }
      else {
        _joystickValues[whichOne].second->setX(0);
      }
    }

    // Move right stick up or down
    if (event.jaxis.axis == 4) {
      if (event.jaxis.value > _joystickDeadzone) {
        _joystickValues[whichOne].second->setY(1);
      }
      else if (event.jaxis.value < -_joystickDeadzone) {
        _joystickValues[whichOne].second->setY(-1);
      }
      else {
        _joystickValues[whichOne].second->setY(0);
      }
    }
  }

  void onJoystickButtonUpOrDown(const SDL_Event& event) {
    auto whichOne = event.jaxis.which;
    _buttonStates[whichOne][event.jbutton.button]
      = !_buttonStates[whichOne][event.jbutton.button];
  }

  void onKeyUpOrDown() {
    _keyState = SDL_GetKeyboardState(0);
  }

  void onMouseButtonUpOrDown(const SDL_Event& event) {
    auto button = -1;

    switch (event.button.button) {
    case SDL_BUTTON_LEFT:
      button = static_cast<int>(MouseButton::left);
      break;

    case SDL_BUTTON_MIDDLE:
      button = static_cast<int>(MouseButton::middle);
      break;

    case SDL_BUTTON_RIGHT:
      button = static_cast<int>(MouseButton::right);
      break;
    }

    if (button < 0) return; // unknown mouse button (gaming mouse?)

    _mouseButtonStates[button] = !_mouseButtonStates[button];
  }

  void onMouseMove(const SDL_Event& event) {
    _mousePos.setX(event.motion.x);
    _mousePos.setY(event.motion.y);
  }

  std::vector<std::pair<Vector2D*, Vector2D*>> _joystickValues;
  std::vector<SDL_Joystick*> _joysticks;
  std::vector<std::vector<bool>> _buttonStates;
  std::vector<bool> _mouseButtonStates;
  Vector2D _mousePos;
  bool _joysticksInitialized;
  int _joystickDeadzone = 10000;
  const Uint8* _keyState = nullptr;
};

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler* InputHandler::Instance() {
  if (!s_pInstance) {
    s_pInstance = new InputHandler();
  }

  return s_pInstance;
}

InputHandler::InputHandler()
  : _pImpl(std::make_unique<Impl>()) {}

InputHandler::~InputHandler() = default;
InputHandler::InputHandler(InputHandler&&) = default;
InputHandler& InputHandler::operator=(InputHandler&&) = default;

int InputHandler::y(int joy, int stick) const {
  return _pImpl->y(joy, stick);
}

int InputHandler::x(int joy, int stick) const {
  return _pImpl->x(joy, stick);
}

bool InputHandler::buttonState(int joy, int buttonNr) const {
  return _pImpl->buttonState(joy, buttonNr);
}

bool InputHandler::mouseButtonState(MouseButton button) const {
  return _pImpl->mouseButtonState(button);
}

Vector2D InputHandler::mousePosition() const {
  return _pImpl->mousePosition();
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
  return _pImpl->isKeyDown(key);
}

void InputHandler::initializeJoysticks() {
  _pImpl->initializeJoysticks();
}

void InputHandler::clean() {
  _pImpl->clean();
}

void InputHandler::update() {
  _pImpl->update();
}

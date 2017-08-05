#include "inputhandler.hh"
#include "game.hh"
#include <string>

My::InputHandler* My::InputHandler::s_pInstance = nullptr;

My::InputHandler* My::InputHandler::Instance() {
  if (!s_pInstance) {
    s_pInstance = new My::InputHandler();
  }

  return s_pInstance;
}

My::InputHandler::InputHandler() : _mousePos(0, 0) {
  for (auto i = 0; i != 3; ++i) {
    _mouseButtonStates.push_back(false);
  }
}

int My::InputHandler::y(int joy, int stick) const {
  if (!_joystickValues.size()) return 0;

  if (stick == 1) {
    return _joystickValues[joy].first->y();
  }
  else if (stick == 2) {
    return _joystickValues[joy].second->y();
  }

  return 0;
}

int My::InputHandler::x(int joy, int stick) const {
  if (!_joystickValues.size()) return 0;

  if (stick == 1) {
    return _joystickValues[joy].first->x();
  }
  else if (stick == 2) {
    return _joystickValues[joy].second->x();
  }

  return 0;
}

bool My::InputHandler::buttonState(int joy, int buttonNr) const {
  return _buttonStates[joy][buttonNr];
}

bool My::InputHandler::mouseButtonState(MouseButton button) const {
  auto i = static_cast<int>(button);
  return _mouseButtonStates[i];
}

My::Vector2D My::InputHandler::mousePosition() const {
  return _mousePos;
}

bool My::InputHandler::isKeyDown(SDL_Scancode key) const {
  if (!_keyState) return false;

  return _keyState[key];
}

void My::InputHandler::initializeJoysticks() {
  if (!SDL_WasInit(SDL_INIT_JOYSTICK)) {
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  }

  if (SDL_NumJoysticks() > 0) {
    for (auto i = 0; i != SDL_NumJoysticks(); ++i) {
      SDL_Joystick* joy = SDL_JoystickOpen(i);

      if (joy) {
        _joysticks.push_back(joy);
        _joystickValues.push_back(std::make_pair(new My::Vector2D(0, 0), new My::Vector2D(0, 0)));

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

void My::InputHandler::clean() {
  if (!_joysticksInitialized) return;

  for (auto i = 0; i != SDL_NumJoysticks(); ++i) {
    SDL_JoystickClose(_joysticks[i]);
  }
}

void My::InputHandler::update() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      My::Game::Instance()->quit();
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

void My::InputHandler::onJoystickAxisMove(const SDL_Event& event) {
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

void My::InputHandler::onJoystickButtonUpOrDown(const SDL_Event& event) {
  auto whichOne = event.jaxis.which;
  _buttonStates[whichOne][event.jbutton.button]
    = !_buttonStates[whichOne][event.jbutton.button];
}

void My::InputHandler::onKeyUpOrDown() {
  _keyState = SDL_GetKeyboardState(0);
}

void My::InputHandler::onMouseButtonUpOrDown(const SDL_Event& event) {
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

void My::InputHandler::onMouseMove(const SDL_Event& event) {
  _mousePos.setX(event.motion.x);
  _mousePos.setY(event.motion.y);
}

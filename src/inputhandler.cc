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

int My::InputHandler::y(int joy, int stick) const {
  if (_joystickValues.size() < joy-1) return 0;

  if (stick == 1) {
    return _joystickValues[joy].first->y();
  }
  else if (stick == 2) {
    return _joystickValues[joy].second->y();
  }

  return 0;
}

int My::InputHandler::x(int joy, int stick) const {
  if (_joystickValues.size() < joy-1) return 0;

  if (stick == 1) {
    return _joystickValues[joy].first->x();
  }
  else if (stick == 2) {
    return _joystickValues[joy].second->x();
  }

  return 0;
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
    if (event.type == SDL_QUIT) {
      My::Game::Instance()->clean();
    }
    else if (event.type == SDL_JOYAXISMOTION) {
      auto whichOne = event.jaxis.which;
    }
  }
}

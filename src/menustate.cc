#include "menustate.hh"
#include "SDL2/SDL.h"

void My::MenuState::update() {
  // TODO
}

void My::MenuState::render() {
  // TODO
}

bool My::MenuState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering MENU state...");
  return true;
}

bool My::MenuState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting MENU state...");
  return true;
}

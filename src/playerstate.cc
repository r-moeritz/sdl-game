#include "playerstate.hh"
#include "SDL2/SDL.h"

void My::PlayerState::update() {

}

void My::PlayerState::render() {

}

bool My::PlayerState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering PLAYER state...");
  return true;
}

bool My::PlayerState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting PLAYER state...");
  return true;
}

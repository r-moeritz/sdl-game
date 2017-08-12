#include "playstate.hh"
#include "SDL2/SDL.h"

My::PlayState::PlayState() {

}

void My::PlayState::update() {

}

void My::PlayState::render() {

}

bool My::PlayState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering PLAY state...");
  return true;
}

bool My::PlayState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting PLAY state...");
  return true;
}

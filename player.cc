#include "player.hh"
#include "SDL2/SDL.h"

My::Player::Player(const My::LoaderParams* pParams)
    : My::SDLGameObject(pParams) {}

void My::Player::update() {
    --_x;
    _curFrame = int((SDL_GetTicks() / 100) * 6);
}

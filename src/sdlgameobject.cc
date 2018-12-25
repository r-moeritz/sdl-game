#include "sdlgameobject.hh"

using namespace MyGame;

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
  : GameObject(pParams),
  _pTextureMgr(TextureManager::Instance()),
  _pInputHandler(InputHandler::Instance()),
  _pGame(Game::Instance()),
  _position(pParams->x(), pParams->y()),
  _velocity(0, 0),
  _acceleration(0, 0) {
  _width = pParams->width();
  _height = pParams->height();
  _textureId = pParams->textureId();
}

void SDLGameObject::update() {
  _velocity += _acceleration;
  _position += _velocity;
}

void SDLGameObject::draw() {
  if (_velocity.x() > 0) {
    _pTextureMgr->drawFrame(_textureId, _position.x(), _position.y(),
                            _width, _height, _curRow, _curFrame,
                            _pGame->renderer(), SDL_FLIP_HORIZONTAL);
  }
  else {
    _pTextureMgr->drawFrame(_textureId, _position.x(), _position.y(),
                            _width, _height, _curRow, _curFrame,
                            _pGame->renderer());
  }
}

#include "sdlgameobject.hh"

My::SDLGameObject::SDLGameObject(const My::LoaderParams* pParams)
  : My::GameObject(pParams), 
  _pTextureMgr(My::TextureManager::Instance()),
  _pInputHandler(My::InputHandler::Instance()),
  _pGame(My::Game::Instance()),
  _position(pParams->x(), pParams->y()),
  _velocity(0, 0),
  _acceleration(0, 0) {
  _width = pParams->width();
  _height = pParams->height();
  _textureId = pParams->textureId();
}

void My::SDLGameObject::update() {
  _velocity += _acceleration;
  _position += _velocity;
}

void My::SDLGameObject::draw() {
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

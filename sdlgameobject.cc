#include "sdlgameobject.hh"

My::SDLGameObject::SDLGameObject(const My::LoaderParams* pParams)
        : My::GameObject(pParams), 
          _pTextureMgr(My::TextureManager::Instance()), 
          _pGame(My::Game::Instance()) {
    _x = pParams->x();
    _y = pParams->y();
    _width = pParams->width();
    _height = pParams->height();
    _textureId = pParams->textureId();
}

void My::SDLGameObject::draw() {
    _pTextureMgr->drawFrame(_textureId, _x, _y, _width, _height,
        _curRow, _curFrame, _pGame->renderer());
}

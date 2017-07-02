#include "gameobject.hh"

void My::GameObject::load(int x, int y, int width, int height, std::string textureId) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _textureId = textureId;
    
    _currentRow = _currentFrame = 1;
}

void My::GameObject::draw(SDL_Renderer* pRenderer) {
    _pTextureMgr->drawFrame(_textureId, _x, _y,
        _width, _height, _currentRow, _currentFrame,
        pRenderer);
}

void My::GameObject::update() {
    _currentFrame = int((SDL_GetTicks() / 100) % 6);
}
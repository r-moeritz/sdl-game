#include "sdlgameobject.hh"
#include "loaderparams.hh"
#include "texturemanager.hh"
#include "game.hh"
#include "SDL2/SDL.h"
#include <string>

using namespace MyGame;

struct SDLGameObject::Impl {

  Impl(std::shared_ptr<LoaderParams> pParams)
    : _pTextureMgr(TextureManager::Instance()),
      _pGame(Game::Instance()),
      _position(pParams->x(), pParams->y()),
      _velocity(0, 0),
      _acceleration(0, 0) {
    _width = pParams->width();
    _height = pParams->height();
    _textureId = pParams->textureId();
  }

  void draw() {
    if (_velocity.x() > 0) {
      _pTextureMgr->drawFrame(_textureId,
                              _position.x(),
                              _position.y(),
                              _width,
                              _height,
                              _curRow,
                              _curFrame,
                              _pGame->renderer(),
                              SDL_FLIP_HORIZONTAL);
    }
    else {
      _pTextureMgr->drawFrame(_textureId,
                              _position.x(),
                              _position.y(),
                              _width,
                              _height,
                              _curRow,
                              _curFrame,
                              _pGame->renderer());
    }
  }

  void update() {
    _velocity += _acceleration;
    _position += _velocity;
  }

  Vector2D position() const {
    return _position;
  }

  int width() const {
    return _width;
  }

  int height() const {
    return _height;
  }

  Vector2D& velocity() {
    return _velocity;
  }

  void velocity(Vector2D const& v) {
    _velocity = v;
  }

  Vector2D& acceleration() {
    return _acceleration;
  }

  void acceleration(Vector2D const& v) {
    _acceleration = v;
  }

  int currentFrame() const {
    return _curFrame;
  }

  void currentFrame(int curFrame) {
    _curFrame = curFrame;
  }

private:

  int _width, _height;
  Vector2D _position;
  Vector2D _velocity;
  Vector2D _acceleration;
  std::string _textureId;

  int _curRow = 0;
  int _curFrame = 0;

  TextureManager* _pTextureMgr;
  Game* _pGame;
};

SDLGameObject::SDLGameObject(std::shared_ptr<LoaderParams> pParams)
  : _pImpl(std::make_unique<Impl>(pParams)) {}

SDLGameObject::~SDLGameObject() = default;
SDLGameObject::SDLGameObject(SDLGameObject&&) = default;
SDLGameObject& SDLGameObject::operator=(SDLGameObject&&) = default;

void SDLGameObject::draw() {
  _pImpl->draw();
}

void SDLGameObject::update() {
  _pImpl->update();
}

Vector2D SDLGameObject::position() const {
  return _pImpl->position();
}

int SDLGameObject::width() const {
  return _pImpl->width();
}

int SDLGameObject::height() const {
  return _pImpl->height();
}

Vector2D& SDLGameObject::velocity()  {
  return _pImpl->velocity();
}

void SDLGameObject::velocity(Vector2D const& v) {
  _pImpl->velocity(v);
}

Vector2D& SDLGameObject::acceleration() {
  return _pImpl->acceleration();
}

void SDLGameObject::acceleration(Vector2D const& v) {
  _pImpl->acceleration(v);
}

int SDLGameObject::currentFrame() const {
  return _pImpl->currentFrame();
}

void SDLGameObject::currentFrame(int curFrame) {
  _pImpl->currentFrame(curFrame);
}

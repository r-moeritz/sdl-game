#ifndef SDLGAMEOBJECT_HH
#define SDLGAMEOBJECT_HH

#include <string>
#include "gameobject.hh"
#include "loaderparams.hh"
#include "texturemanager.hh"
#include "inputhandler.hh"
#include "game.hh"
#include "vector2d.hh"
#include "SDL2/SDL.h"

namespace My {
  class SDLGameObject : public GameObject {
  public:

    virtual void draw();
    virtual void update();
    virtual void clean() = 0;

    inline Vector2D position() const { return _position; };
    inline int width() const { return _width; };
    inline int height() const { return _height; };

  protected:

    SDLGameObject(const LoaderParams*);
    virtual ~SDLGameObject() {}
        
    int _width, _height;
    Vector2D _position;
    Vector2D _velocity;
    Vector2D _acceleration;
    std::string _textureId;

    int _numFrames;
    int _curRow = 0;
    int _curFrame = 0;
        
    TextureManager* _pTextureMgr;
    InputHandler* _pInputHandler;
    Game* _pGame;
  };
}

#endif

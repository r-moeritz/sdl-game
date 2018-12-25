#include "menubutton.hh"

using namespace MyGame;

MenuButton::MenuButton(const LoaderParams* pParams,
                           std::function<void()> callback)
  : SDLGameObject(pParams), _callback(callback) {

}

void MenuButton::draw() {
  SDLGameObject::draw();
}

void MenuButton::update() {
  auto mousePos = _pInputHandler->mousePosition();

  if (mousePos.x() < (_position.x() + _width)
      && mousePos.x() > _position.x()
      && mousePos.y() < (_position.y() + _height)
      && mousePos.y() > _position.y()) {
    _curFrame = static_cast<int>(ButtonState::mouseOver);

    if (_pInputHandler->mouseButtonState(MouseButton::left)
        && _released) {
      _curFrame = static_cast<int>(ButtonState::clicked);
      _released = false;

      _callback();
    }
    else if (_pInputHandler->mouseButtonState(MouseButton::left)) {
      _curFrame = static_cast<int>(ButtonState::mouseOver);
      _released = true;
    }
  }
  else {
    _curFrame = static_cast<int>(ButtonState::mouseOut);
  }
}

void MenuButton::clean() {}

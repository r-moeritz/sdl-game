#include "menubutton.hh"

My::MenuButton::MenuButton(const LoaderParams* pParams)
  : My::SDLGameObject(pParams)  {
}

void My::MenuButton::draw() {
  SDLGameObject::draw();
}

void My::MenuButton::update() {
  auto mousePos = _pInputHandler->mousePosition();

  if (mousePos.x() < (_position.x() + _width)
      && mousePos.x() > _position.x()
      && mousePos.y() < (_position.y() + _height)
      && mousePos.y() > _position.y()) {
    _curFrame = static_cast<int>(ButtonState::mouseOver);

    if (_pInputHandler->mouseButtonState(MouseButton::left)) {
      _curFrame = static_cast<int>(ButtonState::clicked);
    }
  }
  else {
    _curFrame = static_cast<int>(ButtonState::mouseOut);
  }
}

void My::MenuButton::clean() {
  //SDLGameObject::clean();
}

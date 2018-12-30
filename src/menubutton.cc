#include "menubutton.hh"
#include "sdlgameobject.hh"
#include "loaderparams.hh"
#include "inputhandler.hh"

using namespace MyGame;

struct MenuButton::Impl : public SDLGameObject {

  Impl(const LoaderParams* pParams,
       std::function<void()> callback)
    : SDLGameObject(pParams),
      _callback(callback) {}

  void update() override {
    auto pInputHandler = InputHandler::Instance();
    auto mousePos = pInputHandler->mousePosition();

    if (mousePos.x() < (position().x() + width())
        && mousePos.x() > position().x()
        && mousePos.y() < (position().y() + height())
        && mousePos.y() > position().y()) {

      currentFrame(static_cast<int>(ButtonState::mouseOver));

      if (pInputHandler->mouseButtonState(MouseButton::left)
          && _released) {
        currentFrame(static_cast<int>(ButtonState::clicked));
        _released = false;

        _callback();
      }
      else if (pInputHandler->mouseButtonState(MouseButton::left)) {
        currentFrame(static_cast<int>(ButtonState::mouseOver));
        _released = true;
      }
    }
    else {
      currentFrame(static_cast<int>(ButtonState::mouseOut));
    }
  }

  void clean() override {}

private:

  enum class ButtonState { mouseOut, mouseOver, clicked };
  std::function<void()> _callback;
  bool _released;
};

MenuButton::MenuButton(const LoaderParams* pParams,
                       std::function<void()> callback)
  : _pImpl(std::make_unique<Impl>(pParams, callback)) {}

MenuButton::~MenuButton() = default;
MenuButton::MenuButton(MenuButton&&) = default;
MenuButton& MenuButton::operator=(MenuButton&&) = default;

void MenuButton::draw() {
  _pImpl->draw();
}

void MenuButton::update() {
  _pImpl->update();
}

void MenuButton::clean() {
  _pImpl->clean();
}

Vector2D MenuButton::position() const {
  return _pImpl->position();
}

int MenuButton::width() const {
  return _pImpl->width();
}

int MenuButton::height() const {
  return _pImpl->height();
}

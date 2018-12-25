#include "vector2d.hh"

using namespace MyGame;

void Vector2D::normalize() {
  auto l = length();
  if (l > 0) {
    // we won't attempt to divide by zero
    (*this) *= 1 / l;
  }
}

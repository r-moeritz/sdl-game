#include "player.hh"

void My::Player::update() {
    My::GameObject::update();
    ++_x;
}

void My::Player::clean() {
}
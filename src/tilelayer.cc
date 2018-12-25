#include "tilelayer.hh"
#include "tileset.hh"
#include "vector2d.hh"

using namespace MyGame;

TileLayer::TileLayer(int tileSize, std::vector<TilesetPtr> const& tilesets)
  : _tileSize(tileSize), _tilesets(tilesets) {

}

void TileLayer::update() {

}

void TileLayer::render() {

}

TilesetPtr TileLayer::getTilesetByID(int tileID) const {
  TilesetPtr b;

  return b;
}

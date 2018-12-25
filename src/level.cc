#include "level.hh"
#include "tileset.hh"
#include "layer.hh"

using namespace MyGame;

void Level::update() {
  for (auto& pLayer : _layers) {
    pLayer->update();
  }
}

void Level::render() {
  for (auto& pLayer : _layers) {
    pLayer->render();
  }
}

std::vector<TilesetPtr>& Level::tilesets() {
  return _tilesets;
}

std::vector<LayerPtr>& Level::layers() {
  return _layers;
}

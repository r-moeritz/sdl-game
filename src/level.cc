#include "level.hh"
#include "tileset.hh"
#include "layer.hh"

void My::Level::update() {
  for (auto& pLayer : _layers) {
    pLayer->update();
  }
}

void My::Level::render() {
  for (auto& pLayer : _layers) {
    pLayer->render();
  }
}

std::vector<TilesetPtr>& My::Level::tilesets() {
  return _tilesets;
}

std::vector<LayerPtr>& My::Level::layers() {
  return _layers;
}

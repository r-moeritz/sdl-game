#include "level.hh"
#include "tileset.hh"
#include "layer.hh"

using namespace MyGame;

struct Level::Impl {
  Impl()
    : _pTilesets(std::make_shared<std::vector<TilesetPtr>>()),
      _pLayers(std::make_shared<std::vector<LayerPtr>>()) {}

  void update() {
    for (auto& pLayer : *_pLayers) {
      pLayer->update();
    }
  }

  void render() {
    for (auto& pLayer : *_pLayers) {
      pLayer->render();
    }
  }

  TilesetPtrVectorPtr tilesets() {
    return _pTilesets;
  }

  LayerPtrVectorPtr layers() {
    return _pLayers;
  }

private:

  TilesetPtrVectorPtr _pTilesets;
  LayerPtrVectorPtr _pLayers;
};

Level::Level()
  : _pImpl(std::make_unique<Impl>()) {}

Level::~Level() = default;

Level::Level(Level&&) = default;

Level& Level::operator=(Level&&) = default;

void Level::update() {
  _pImpl->update();
}

void Level::render() {
  _pImpl->render();
}

TilesetPtrVectorPtr Level::tilesets() {
  return _pImpl->tilesets();
}

LayerPtrVectorPtr Level::layers() {
  return _pImpl->layers();
}

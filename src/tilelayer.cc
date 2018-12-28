#include "tilelayer.hh"
#include "tileset.hh"
#include "vector2d.hh"

using namespace MyGame;

struct TileLayer::Impl {
  Impl(int tileSize, TilesetPtrVectorPtr pTilesets)
    : _tileSize(tileSize),
      _pTilesets(pTilesets) {}

  void update() {
    // TODO
  }

  void render() {
    // TODO
  }

  void setTileIDs(std::vector<std::vector<int>> const& data) {
    _tileIDs = data;
  }

  void setTileSize(int tileSize) {
    _tileSize = tileSize;
  }

  TilesetPtr getTilesetByID(int tileID) const {
    // TODO
    return nullptr;
  }

private:

  int _numColumns;
  int _numRows;
  int _tileSize;

  Vector2DPtr _pPosition;
  Vector2DPtr _pVelocity;

  TilesetPtrVectorPtr _pTilesets;
  std::vector<std::vector<int>> _tileIDs;
};

TileLayer::TileLayer(int tileSize, TilesetPtrVectorPtr pTilesets)
  : _pImpl(std::make_unique<Impl>(tileSize, pTilesets)) {}

TileLayer::~TileLayer() = default;

TileLayer::TileLayer(TileLayer&&) = default;

TileLayer& TileLayer::operator=(TileLayer&&) = default;

void TileLayer::update() {
  _pImpl->update();
}

void TileLayer::render() {
  _pImpl->render();
}

void TileLayer::setTileIDs(std::vector<std::vector<int>> const& data) {
  _pImpl->setTileIDs(data);
}

void TileLayer::setTileSize(int tileSize) {
  _pImpl->setTileSize(tileSize);
}

TilesetPtr TileLayer::getTilesetByID(int tileID) const {
  return _pImpl->getTilesetByID(tileID);
}

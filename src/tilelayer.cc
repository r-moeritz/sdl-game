#include "tilelayer.hh"
#include "tileset.hh"
#include "vector2d.hh"
#include "game.hh"
#include "texturemanager.hh"

using namespace MyGame;

struct TileLayer::Impl {
  Impl(int tileSize, TilesetPtrVectorPtr pTilesets)
    : _tileSize(tileSize),
      _pTilesets(pTilesets),
      _position(0,0),
      _velocity(0,0),
      _pTextureManager(TextureManager::Instance()) {
    _numColumns = (Game::Instance()->width() / _tileSize);
    _numRows = (Game::Instance()->height() / _tileSize);
  }

  void update() {
    _position += _velocity;
  }

  void render() {
    auto x = int(_position.x()) / _tileSize;
    auto y = int(_position.y()) / _tileSize;

    auto x2 = int(_position.x()) % _tileSize;
    auto y2 = int(_position.y()) % _tileSize;

    for (auto i = 0; i != _numRows; ++i) {
      for (auto k = 0; k != _numColumns; ++k) {
        auto id = _tileIDs[k + x][i + y];

        if (id == 0) continue;

        auto pTs = getTilesetByID(id);

        --id;

        _pTextureManager->drawTile(pTs->name,
                                   pTs->margin,
                                   pTs->spacing,
                                   (k * _tileSize) - x2,
                                   (i * _tileSize) - y2,
                                   _tileSize,
                                   _tileSize,
                                   (id - (pTs->firstGridID - 1)) / pTs->numColumns,
                                   (id - (pTs->firstGridID - 1)) % pTs->numColumns,
                                   Game::Instance()->renderer());
      }
    }
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

  Vector2D _position;
  Vector2D _velocity;

  TilesetPtrVectorPtr _pTilesets;
  std::vector<std::vector<int>> _tileIDs;

  TextureManager* _pTextureManager;
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

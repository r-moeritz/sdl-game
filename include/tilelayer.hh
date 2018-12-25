#ifndef TILELAYER_HH
#define TILELAYER_HH

#include "layer.hh"
#include <vector>
#include <memory>

namespace MyGame {
  struct Tileset;
  struct Vector2D;
  using Vector2DPtr = std::shared_ptr<Vector2D>;
  using TilesetPtr = std::shared_ptr<Tileset>;

  struct TileLayer : public Layer {

    TileLayer(int tileSize, std::vector<TilesetPtr> const& tileSets);

    virtual void update();
    virtual void render();

    void setTileIDs(std::vector<std::vector<int>> const& data) {
      _tileIDs = data;
    }

    void setTileSize(int tileSize) {
      _tileSize = tileSize;
    }

    TilesetPtr getTilesetByID(int tileID) const;

  private:

    int _numColumns;
    int _numRows;
    int _tileSize;

    Vector2DPtr _pPosition;
    Vector2DPtr _pVelocity;

    std::vector<TilesetPtr> const& _tilesets;
    std::vector<std::vector<int>> _tileIDs;
  };
}

#endif // #ifndef TILELAYER_HH

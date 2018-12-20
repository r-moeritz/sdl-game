#ifndef TILELAYER_HH
#define TILELAYER_HH

#include "layer.hh"
#include <vector>
#include <memory>

namespace My {
  struct TilesetPtr;
  struct Vector2DPtr;

  class TileLayer : public Layer {
  public:

    TileLayer(int tileSize, std::vector<TilesetPtr>& const tileSets);

    virtual void update();
    virtual void render();

    void setTileIDs(std::vector<std::vector<int>& const data) {
      _tileIDs = data;
    }

    void setTileSize(int tileSize) {
      _tileSize = tileSize;
    }

    TilesetPtr getTilesetByID(int tileID);

  private:

    int _numColumns;
    int _numRows;
    int _tileSize;

    Vector2DPtr _pPosition;
    Vector2DPtr _pVelocity;

    const std::vector<TilesetPtr> &_tilesets;
    const std::vector<std::vector<int>> &_tileIDs;
  };
}

#endif // #ifndef TILELAYER_HH

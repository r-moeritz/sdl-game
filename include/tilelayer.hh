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
  using TilesetPtrVectorPtr = std::shared_ptr<std::vector<TilesetPtr>>;

  struct TileLayer : public Layer {

    TileLayer(int tileSize, TilesetPtrVectorPtr pTileSets);
    ~TileLayer();
    TileLayer(TileLayer&&);
    TileLayer& operator=(TileLayer&&);

    void update() override;
    void render() override;

    void setTileIDs(std::vector<std::vector<int>> const& data);
    void setTileSize(int tileSize);
    TilesetPtr getTilesetByID(int tileID) const;

  private:

    struct Impl;
    std::unique_ptr<Impl> _pImpl;
  };
}

#endif // #ifndef TILELAYER_HH

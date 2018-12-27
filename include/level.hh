#ifndef LEVEL_HH
#define LEVEL_HH

#include "levelparser.hh"
#include <vector>
#include <memory>

namespace MyGame {
  struct Layer;
  struct Tileset;

  using LayerPtr = std::shared_ptr<Layer>;
  using TilesetPtr = std::shared_ptr<Tileset>;

  using TilesetPtrVectorPtr = std::shared_ptr<std::vector<TilesetPtr>>;
  using LayerPtrVectorPtr = std::shared_ptr<std::vector<LayerPtr>>;

  struct Level {

    Level();
    ~Level();
    Level(Level&&);
    Level& operator=(Level&&);

    void update();
    void render();

    TilesetPtrVectorPtr tilesets();
    LayerPtrVectorPtr layers();

  private:

    struct Impl;
    std::unique_ptr<Impl> _pImpl;
  };
}

#endif // #ifndef LEVEL_HH

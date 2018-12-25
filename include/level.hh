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

  struct Level {

    ~Level() {}

    void update();
    void render();

    std::vector<TilesetPtr>& tilesets();
    std::vector<LayerPtr>& layers();

  private:

    friend class LevelParser;
    Level();

    std::vector<TilesetPtr> _tilesets;
    std::vector<LayerPtr> _layers;
  };
}

#endif // #ifndef LEVEL_HH

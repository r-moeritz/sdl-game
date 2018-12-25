#ifndef LEVELPARSER_HH
#define LEVELPARSER_HH

#include "tileset.hh"
#include <memory>
#include <vector>

struct TiXmlElement;

namespace MyGame {

  struct Level;
  struct Layer;

  using LevelPtr = std::shared_ptr<Level>;
  using LayerPtr = std::shared_ptr<Layer>;

  using TilesetVectorPtr = std::shared_ptr<std::vector<Tileset>>;
  using LayerPtrVectorPtr = std::shared_ptr<std::vector<LayerPtr>>;

  struct LevelParser {

    LevelPtr parseLevel(const char* levelFile);

  private:

    void parseTilesets(TiXmlElement* pTilesetRoot,
                       TilesetVectorPtr pTilesets);

    void parseTileLayer(TiXmlElement* pTileElement,
                        LayerPtrVectorPtr pLayers,
                        TilesetVectorPtr pTilesets);

    int _tileSize;
    int _width;
    int _height;

  };
}

#endif // #ifndef LEVELPARSER_HH

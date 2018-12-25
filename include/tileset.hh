#ifndef TILESET_HH
#define TILESET_HH

#include <string>

namespace MyGame {
  struct Tileset {
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
  };
}

#endif // #ifndef TILESET_HH

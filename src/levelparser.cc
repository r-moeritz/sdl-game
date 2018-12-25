#include "levelparser.hh"
#include "level.hh"
#include "tinyxml.h"

using namespace MyGame;

LevelPtr LevelParser::parseLevel(const char* levelFile) {
  // Load map xml
  TiXmlDocument levelDoc;
  levelDoc.LoadFile(levelFile);

  auto pLevel = std::make_shared<Level>();

  auto pRoot = levelDoc.RootElement();

  pRoot->Attribute("tilewidth", &_tileSize);
  pRoot->Attribute("width", &_width);
  pRoot->Attribute("height", &_height);

  for (auto pe = pRoot->FirstChildElement();
       pe != nullptr;
       pe = pe->NextSiblingElement()) {
    // Parse the tilesets
    if (pe->Value() == std::string("tileset")) {
      parseTilesets(pe, pLevel->tilesets());
    }
    // Parse any object layers
    else if (pe->Value() == std::string("layer")) {
      parseTileLayer(pe, pLevel->layers(), pLevel->tilesets())
    }
  }

  return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot,
                                TilesetVectorPtr pTilesets) {

}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement,
                                 LayerPtrVectorPtr pLayers,
                                 TilesetVectorPtr pTilesets) {

}

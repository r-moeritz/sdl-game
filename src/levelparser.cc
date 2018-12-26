#include "levelparser.hh"
#include "level.hh"
#include "texturemanager.hh"
#include "game.hh"
#include <tinyxml.h>
#include <cppcodec/base64_rfc4648.hpp>
#include <zstr.hpp>
#include <stdexcept>

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
  // Add tileset to texture manager
  TextureManager::instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"),
                                   pTilesetRoot->Attribute("name"),
                                   Game::instance()->renderer());

  // Create a tileset object
  Tileset ts;
  pTilesetRoot->FirstChildElement()->Attribute("width", &ts.width);
  pTilesetRoot->FirstChildElement()->Attribute("height", &ts.height);
  pTilesetRoot->Attribute("firstgid", &ts.firstGridID);
  pTilesetRoot->Attribute("tilewidth", &ts.tileWidth);
  pTilesetRoot->Attribute("tileheight", &ts.tileHeight);
  pTilesetRoot->Attribute("spacing", &ts.spacing);
  pTilesetRoot->Attribute("margin", &ts.margin);
  ts.name = pTilesetRoot->Attribute("name");
  ts.numColumns = ts.width / (ts.tileWidth + ts.spacing);

  pTilesets->push_back(ts);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement,
                                 LayerPtrVectorPtr pLayers,
                                 TilesetVectorPtr pTilesets) {
  using base64 = cppcodec::base64_rfc4648;

  auto pTileLayer = std::make_shared<TileLayer>(_tileSize, *pTilesets);

  // Tile data
  std::vector<std::vector<int>> data;

  TiXmlElement* pDataNode = nullptr;

  for (auto pe = pTileElement->FirstChildElement();
       pe != nullptr;
       pe = pe->NextSiblingElement()) {
    if (pe->Value() == std::string("data")) {
      pDataNode = pe;
      break;
    }
  }

  if (!pDataNode) {
    throw std::runtime_error("No data node");
  }

  std::string text = pDataNode->FirstChild()->ToText()->Value();
  std::vector<unsigned> decodedIds = base64::decode(text);

  // TODO Uncompress decodedIds
}

#include "levelparser.hh"
#include "tileset.hh"
#include "level.hh"
#include "texturemanager.hh"
#include "tilelayer.hh"
#include "game.hh"
#include "util.hh"
#include <tinyxml2.h>
#include <zlib.h>
#include <stdexcept>

using namespace MyGame;
using namespace tinyxml2;

struct LevelParser::Impl {
  LevelPtr parseLevel(const char* levelFile) {
    // Load map xml
    XMLDocument levelDoc;
    levelDoc.LoadFile(levelFile);

    auto pLevel = std::make_shared<Level>();

    auto pRoot = levelDoc.RootElement();

    _tileSize = pRoot->IntAttribute("tilewidth");
    _width = pRoot->IntAttribute("width");
    _height = pRoot->IntAttribute("height");

    for (auto pe = pRoot->FirstChildElement();
         pe != nullptr;
         pe = pe->NextSiblingElement()) {
      // Parse the tilesets
      if (pe->Value() == std::string("tileset")) {
        parseTilesets(pe, pLevel->tilesets());
      }
      // Parse any object layers
      else if (pe->Value() == std::string("layer")) {
        parseTileLayer(pe, pLevel->layers(), pLevel->tilesets());
      }
    }

    return pLevel;
  }

private:

  void parseTilesets(XMLElement* pTilesetRoot,
                     TilesetPtrVectorPtr pTilesets) {
    std::string assetPath = "assets/";

    // Add tileset to texture manager
    std::string fileName = pTilesetRoot->FirstChildElement()->Attribute("source");
    auto fullPath = assetPath + fileName;
    TextureManager::Instance()->load(fullPath,
                                     pTilesetRoot->Attribute("name"),
                                     Game::Instance()->renderer());

    // Create a tileset
    auto pTs = std::make_shared<Tileset>();
    pTs->width = pTilesetRoot->FirstChildElement()->IntAttribute("width");
    pTs->height = pTilesetRoot->FirstChildElement()->IntAttribute("height");
    pTs->firstGridID = pTilesetRoot->IntAttribute("firstgid");
    pTs->tileWidth = pTilesetRoot->IntAttribute("tilewidth");
    pTs->tileHeight = pTilesetRoot->IntAttribute("tileheight");
    pTs->spacing = pTilesetRoot->IntAttribute("spacing");
    pTs->margin = pTilesetRoot->IntAttribute("margin");
    pTs->name = pTilesetRoot->Attribute("name");
    pTs->numColumns = pTs->width / (pTs->tileWidth + pTs->spacing);

    // ... and add it to our collection
    pTilesets->push_back(pTs);
  }

  void parseTileLayer(XMLElement* pTileElement,
                      LayerPtrVectorPtr pLayers,
                      TilesetPtrVectorPtr pTilesets) {
    auto pTileLayer = std::make_shared<TileLayer>(_tileSize, pTilesets);

    // Tile data
    std::vector<std::vector<int>> data;

    XMLElement* pDataNode = nullptr;

    for (auto pe = pTileElement->FirstChildElement();
         pe != nullptr;
         pe = pe->NextSiblingElement()) {
      if (pe->Value() == std::string("data")) {
        pDataNode = pe;
        break;
      }
    }

    if (!pDataNode) {
      throw std::runtime_error("No data element");
    }

    auto textNode = pDataNode->FirstChild()->ToText();
    auto encodedIds = trim(textNode->Value());
    auto decodedIds = decodeBase64(encodedIds);

    auto numGids = _width * _height * sizeof(int);
    std::vector<unsigned> gids = { numGids };
    uncompress(reinterpret_cast<Bytef*>(&gids[0]),
               &numGids,
               reinterpret_cast<Bytef*>(const_cast<char*>(decodedIds.c_str())),
               decodedIds.size());

    std::vector<int> layerRow = { _width };

    for (auto r = 0; r != _height; ++r) {
      data.push_back(layerRow);

      for (auto c = 0; c != _width; ++c) {
        data[r][c] = gids[r * _width + c];
      }
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
  }

  int _tileSize;
  int _width;
  int _height;
};

LevelParser::LevelParser()
  : _pImpl(std::make_unique<Impl>()) {}

LevelParser::~LevelParser() = default;

LevelParser::LevelParser(LevelParser&&) = default;

LevelParser& LevelParser::operator=(LevelParser&&) = default;

LevelPtr LevelParser::parseLevel(const char* levelFile) {
  return _pImpl->parseLevel(levelFile);
}

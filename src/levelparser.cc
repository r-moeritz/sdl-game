#include "levelparser.hh"
#include "tileset.hh"
#include "level.hh"
#include "texturemanager.hh"
#include "tilelayer.hh"
#include "game.hh"
#include "util.hh"
#include "objectlayer.hh"
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
      // Parse any object or tile layers
      else if (pe->Value() == std::string("objectgroup")
               || pe->Value() == std::string("layer")) {
        if (pe->FirstChildElement()->Value() == std::string("object")) {
          parseObjectLayer(pe, pLevel->layers());
        }
        else if (pe->FirstChildElement()->Value() == std::string("data")) {
          parseTileLayer(pe, pLevel->layers(), pLevel->tilesets());
        }
      }
      // Parse the textures needed for this level
      else if (pe->Value() == std::string("property")) {
        parseTextures(pe);
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

    auto decodedIdsSize = decodedIds.size();
    auto idsSize = _width * _height * sizeof(int);
    std::vector<int> ids(_width * _height);

    auto rc = uncompress2(reinterpret_cast<Bytef*>(&ids[0]),
                          &idsSize,
                          reinterpret_cast<const Bytef*>(&decodedIds[0]),
                          &decodedIdsSize);

    for (auto r = 0; r != _height; ++r) {
      std::vector<int> layerRow(_width);
      data.push_back(layerRow);

      for (auto c = 0; c != _width; ++c) {
        data[r][c] = ids[r * _width + c];
      }
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
  }

  void parseTextures(XMLElement* pTextureRoot) {
    TextureManager::Instance()->load(pTextureRoot->Attribute("value"),
                                     pTextureRoot->Attribute("name"),
                                     Game::Instance()->renderer());
  }

  void parseObjectLayer(XMLElement* pObjectElement,
                        LayerPtrVectorPtr pLayers) {
    auto pObjectLayer = std::make_shared<ObjectLayer>();

    for (auto pe = pObjectElement->FirstChildElement();
         pe != nullptr; pe = pe->NextSiblingElement()) {
      if (pe->Value() == std::string("object")) {
        auto x = pe->IntAttribute("x");
        auto y = pe->IntAttribute("y");

        int numFrames;
        int height;
        int width;
        std::string textureId;
        int animSpeed;
        std::string callbackId;

        // Read property values
        for (auto pProperties = pe->FirstChildElement();
             pProperties = nullptr; pProperties = pProperties->NextSiblingElement()) {
          if (pProperties->Value() == std::string("properties")) {
            for (auto pProp = pProperties->FirstChildElement();
                 pProp != nullptr; pProp = pProp->NextSiblingElement()) {
              if (pProp->Value() == std::string("property")) {
                auto propName = pProp->Attribute("name");

                if (propName == std::string("numFrames")) {
                  numFrames = pProp->IntAttribute("value");
                }
                else if (propName == std::string("textureHeight")) {
                  height = pProp->IntAttribute("value");
                }
                else if (propName == std::string("textureId")) {
                  textureId = pProp->Attribute("value");
                }
                else if (propName == std::string("textureWidth")) {
                  width = pProp->IntAttribute("value");
                }
                else if (propName == std::string("callbackId")) {
                  callbackId = pProp->Attribute("callbackId");
                }
                else if (propName == std::string("animSpeed")) {
                  animSpeed = pProp->IntAttribute("animSpeed");
                }
              }
            }
          }
        }

        auto pGameObj = GameObjectFactory::Instance()->create(pe->Attribute("type"));
        auto pLoaderParams = std::make_shared<LoaderParams>(x, y, width, height, textureId,
                                                            numFrames, callbackId, animSpeed);
        pGameObj->load(pLoaderParams);

        pObjectLayer->gameObjects()->push_back(pGameObj);
      }
    }

    pLayers->push_back(pObjectLayer);
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

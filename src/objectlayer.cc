#include "objectlayer.hh"
#include "gameobject.hh"

using namespace MyGame;

struct MyGame::Impl {
  Impl()
    : _pGameObjects(std::make_shared<GameObjectPtrVecPtr>())
  {}


  void update() {
    for (auto& pObj : *_pGameObjects) {
      pObj->update();
    }
  }

  void render() {
    for (auto& pObj : *_pGameObjects) {
      pObj->draw();
    }
  }

  GameObjectPtrVectorPtr gameObjects() {
    return _pGameObjects;
  }

private:

  GameObjectPtrVectorPtr _pGameObjects;
};

ObjectLayer::ObjectLayer()
  : _pImpl(std::make_unique<Impl>) {}

ObjectLayer::~ObjectLayer() = default;
ObjectLayer::ObjectLayer(ObjectLayer&&) = default;
ObjectLayer& ObjectLayer::operator=(ObjectLayer&&) = default;

void ObjectLayer::update() {
  _pImpl->update();
}

void ObjectLayer::render() {
  _pImpl->render();
}

GameObjectPtrVectorPtr ObjectLayer::gameObjects() {
  return _pImpl->gameObjects();
}

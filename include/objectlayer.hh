#ifndef OBJECTLAYER_HH
#define OBJECTLAYER_HH

#include <vector>
#include <memory>

namespace MyGame {
  struct GameObject;
  using GameObjectPtr = std::shared_ptr<GameObject>;
  using GameObjectPtrVectorPtr = std::shared_ptr<std::vector<GameObjectPtr>>;

  struct ObjectLayer : public Layer {

    ObjectLayer();
    ~ObjectLayer();
    ObjectLayer(ObjectLayer&&);
    ObjectLayer& operator=(ObjectLayer&&);

    void update() override;
    void render() override;

    GameObjectPtrVectorPtr gameObjects();

  private:

    struct Impl;
    std::unique_ptr<Impl> _pImpl;
  };
}

#endif // #ifndef OBJECTLAYER_HH

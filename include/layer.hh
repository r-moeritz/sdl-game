#ifndef LAYER_HH
#define LAYER_HH

namespace MyGame {
  struct Layer {

    virtual void render() = 0;
    virtual void update() = 0;

  protected:

    virtual ~Layer() {}
  };
}

#endif // LAYER_HH

#ifndef LAYER_HH
#define LAYER_HH

namepsace My {
  class Layer {
  public:

    virtual void render() = 0;
    virtual void update() = 0;

  protected:

    virtual ~Layer() {}
  };
}

#endif // LAYER_HH

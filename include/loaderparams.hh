#ifndef LOADERPARAMS_HH
#define LOADERPARAMS_HH

#include <string>

namespace My {
    class LoaderParams {
    public:

      LoaderParams(int x, int y, int width, int height, const std::string& textureId)
        : _x(x), _y(y), _width(width), _height(height),
          _textureId(textureId) {}
 
      inline int x() const { return _x; }
      inline int y() const { return _y; }
      inline int width() const { return _width; }
      inline int height() const { return _height; }
      inline std::string textureId() const { return _textureId; }

    private:

      int _x, _y, _width, _height;
      std::string _textureId;
    };
}

#endif

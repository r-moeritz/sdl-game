#ifndef VECTOR2D_HH
#define VECTOR2D_HH

namespace My {
  class Vector2D {
  public:
    Vector2D(float x, float y) : _x(x), _y(y) {}

    inline float x() const { return _x; }
    inline float y() const { return _y; }

    inline void setX(float x) { _x = x; }
    inline void setY(float y) { _y = y; }

    inline float length() const {
      return sqrt(_x * _x + _y * _y); 
    }
    
    Vector2D operator+(const Vector2D& v2) const {
      return Vector2D(_x + v2._x, _y + v2._y);
    }
    friend Vector2D& operator +=(Vector2D& v1, const Vector2D& v2) {
      v1._x += v2._x;
      v1._y += v2._y;
      return v1;
    }

  private:
    float _x, _y;
  };
}
#endif

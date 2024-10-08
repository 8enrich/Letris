#pragma once
template<typename T>
class Vec2 {
public:
  Vec2() = default;
  constexpr Vec2(T x, T y):
    x(x), y(y)
  {}
  constexpr Vec2(T n):
    x(n), y(n)
  {}
  constexpr T GetX() const {return x;}
  constexpr T GetY() const {return y;}
  constexpr void SetX(T x_in) {x = x_in;}
  constexpr void SetY(T y_in) {y = y_in;}
public:
  bool operator>=(const T rhs) const {return x >= rhs && y >= rhs;} 
  bool operator>=(const Vec2& rhs) const {return x >= rhs.x && y >= rhs.y;} 
  bool operator>(const Vec2& rhs) const {return x > rhs.x && y > rhs.y;} 
  bool operator<=(const T rhs) const {return x <= rhs && y <= rhs;} 
  bool operator<=(const Vec2& rhs) const {return x <= rhs.x && y <= rhs.y;} 
  bool operator<(const Vec2& rhs) const {return x < rhs.x && y < rhs.y;} 
  bool operator==(const Vec2& rhs) const { return (x == rhs.x) && (y == rhs.y); }
  bool operator!=(const Vec2& rhs) const { return !(*this == rhs); }
  
  Vec2 operator+(const Vec2& rhs) const{ return {x + rhs.x, y + rhs.y}; }
  Vec2 operator+(const T rhs) const { return {x + rhs, y + rhs}; } 
  Vec2& operator+=(const Vec2& rhs){ return *this = *this + rhs; }
  
  Vec2 operator-(const Vec2& rhs) const { return {x - rhs.x, y - rhs.y}; }
  Vec2 operator-(const T rhs) const { return {x - rhs, y - rhs}; } 
  Vec2& operator-=(const Vec2& rhs){ return *this = *this - rhs; }

  Vec2 operator*(const Vec2& rhs) const { return {x * rhs.x, y * rhs.y}; }

  Vec2 operator*(const T rhs) const { return {x * rhs, y * rhs}; }

  Vec2& operator*=(const Vec2& rhs){ *this = *this * rhs; }

  explicit operator Vec2<double>() const { return Vec2<double>{static_cast<double>(x), static_cast<double>(y)}; }
  explicit operator Vec2<float>() const { return Vec2<float>{static_cast<float>(x), static_cast<float>(y)}; }

private:
  T x;
  T y;
};

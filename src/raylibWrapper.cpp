#include "../include/raylibWrapper.hpp"
#include <assert.h>
#include <raylib.h>
void ray_wrapper::DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color){
  assert((pos >= 0 && pos < Vec2{GetScreenWidth(), GetScreenHeight()}));
  DrawRectangle(pos.GetX(), pos.GetY(), widthHeight.GetX(), widthHeight.GetY(), color);
}

#include "rectangle.hpp"
#include <stdexcept>
#include "base-types.hpp"

grebenshchikov::Rectangle::Rectangle(point_t pos, double width, double height):
  rect_{width, height, pos}
{
  if (!(width > 0.0 && height > 0.0))
  {
    throw std::invalid_argument("Rectangle dimensions must be positive\n");
  }
}

double grebenshchikov::Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

grebenshchikov::rectangle_t grebenshchikov::Rectangle::getFrameRect() const
{
  return rect_;
}

void grebenshchikov::Rectangle::move(point_t new_pos)
{
  rect_.pos = new_pos;
}

void grebenshchikov::Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void grebenshchikov::Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::logic_error("Scale factor must be positive\n");
  }
  rect_.height *= factor;
  rect_.width *= factor;
}

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using std::size_t;

namespace grebenshchikov
{
  void printShapes(const Shape* const shapes[], size_t count);
  void scaleShapes(Shape* const shapes[], size_t count, point_t pos, double factor);
}

void grebenshchikov::printShapes(const Shape* const shapes[], size_t count)
{
  constexpr double half = 0.5;
  double total_area = 0.0;

  const rectangle_t frame = shapes[0]->getFrameRect();
  double left = frame.pos.x - frame.width * half;
  double right = frame.pos.x + frame.width * half;
  double bottom = frame.pos.y - frame.height * half;
  double top = frame.pos.y + frame.height * half;

  for (size_t i = 0; i < count; i++)
  {
    const double area = shapes[i]->getArea();
    const rectangle_t frame_rect = shapes[i]->getFrameRect();

    const double current_left = frame_rect.pos.x - frame_rect.width * half;
    const double current_right = frame_rect.pos.x + frame_rect.width * half;
    const double current_bottom = frame_rect.pos.y - frame_rect.height * half;
    const double current_top = frame_rect.pos.y + frame_rect.height * half;

    if (current_left < left)
    {
      left = current_left;
    }
    if (current_right > right)
    {
      right = current_right;
    }
    if (current_top > top)
    {
      top = current_top;
    }
    if (current_bottom < bottom)
    {
      bottom = current_bottom;
    }

    std::cout << area << ' ' << frame_rect.height << ' ' << frame_rect.width << ' ' << frame_rect.pos.x << ' '
              << frame_rect.pos.y << '\n';
    total_area += area;
  }

  const point_t total_center{(left + right) * half, (bottom + top) * half};
  const double total_width = right - left;
  const double total_height = top - bottom;

  std::cout << total_area << '\n';
  std::cout << total_height << ' ' << total_width << ' ' << total_center.x << ' ' << total_center.y << '\n';
}

void grebenshchikov::scaleShapes(Shape* const shapes[], size_t count, point_t pos, double factor)
{
  for (size_t i = 0; i < count; i++)
  {
    const point_t old_center = shapes[i]->getFrameRect().pos;
    const point_t new_center{pos.x + (old_center.x - pos.x) * factor, pos.y + (old_center.y - pos.y) * factor};

    shapes[i]->scale(factor);
    shapes[i]->move(new_center);
  }
}

int main()
{
  constexpr grebenshchikov::point_t rectangle_center{1.0, 3.0};
  constexpr double rectangle_width = 4.0;
  constexpr double rectangle_height = 2.0;
  constexpr grebenshchikov::point_t circle_center{6.0, 3.0};
  constexpr double circle_radius = 1.0;
  grebenshchikov::Rectangle rect(rectangle_center, rectangle_width, rectangle_height);
  grebenshchikov::Circle circle(circle_center, circle_radius);

  constexpr int memory_error = 2;
  constexpr size_t count = 2;
  grebenshchikov::Shape** const shapes
      = static_cast< grebenshchikov::Shape** >(std::malloc(count * sizeof(grebenshchikov::Shape*)));

  if (shapes == nullptr)
  {
    std::cerr << "Not enough memory\n";
    return memory_error;
  }

  shapes[0] = &rect;
  shapes[1] = &circle;

  grebenshchikov::printShapes(shapes, count);

  grebenshchikov::point_t pos{};
  double factor = 0.0;
  if (!(std::cin >> pos.x >> pos.y >> factor) || !(factor > 0.0))
  {
    std::cerr << "Expected coordinates and a positive scale factor\n";
    std::free(shapes);
    return 1;
  }

  grebenshchikov::scaleShapes(shapes, count, pos, factor);
  grebenshchikov::printShapes(shapes, count);

  std::free(shapes);
  return 0;
}

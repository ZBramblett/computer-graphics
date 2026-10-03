#pragma once

#include "Shape.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class ShapeList : public Shape
{
public:
  ShapeList() {}
  ShapeList(shared_ptr<Shape> object);

  void clear();
  void add(shared_ptr<Shape> object);
  bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const override;

private:
  std::vector<shared_ptr<Shape>> objects;
};

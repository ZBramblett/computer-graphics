#pragma once
#include "ray.h"
#include "vec3.h"
#include "color.h"

struct HitRecord
{
  point3 p;
  vec3 normal;
  double t;
  color shapeColor;
};

class Shape
{
public:
  virtual ~Shape() = default;
  Shape();
  Shape(color shapeColor);
  virtual bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const = 0;

protected:
  color shapeColor;
};

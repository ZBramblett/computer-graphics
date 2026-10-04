#pragma once
#include "ray.h"
#include "vec3.h"

struct HitRecord
{
  point3 p;
  vec3 normal;
  double t;
};

class Shape
{
public:
  virtual ~Shape() = default;
  virtual bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const = 0;
};

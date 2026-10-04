#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
  Triangle(point3 a, point3 b, point3 c);

  bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const override;

protected:
  point3 a;
  point3 b;
  point3 c;
};
#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
  Sphere(point3 sphereCenter, double sphereRadius);

  bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const override;

protected:
  point3 center;
  double radius;
};

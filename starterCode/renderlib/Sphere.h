#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
  Sphere(point3 sphereCenter, double sphereRadius, shared_ptr<Shader> shader = nullptr);

  bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const override;
  BoundingBox boundingBox() const override;
  point3 _center() const override;

protected:
  point3 center;
  double radius;
  BoundingBox bbox;
};

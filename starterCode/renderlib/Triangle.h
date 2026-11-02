#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
  Triangle(point3 a, point3 b, point3 c, shared_ptr<Shader> shader = nullptr);

  bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const override;
  BoundingBox boundingBox() const override;
  point3 _center() const override;

protected:
  point3 a;
  point3 b;
  point3 c;
  BoundingBox bbox;
  point3 center;
};
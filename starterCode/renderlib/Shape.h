#pragma once
#include "ray.h"
#include "HitRecord.h"
#include "BoundingBox.h"

class Shape
{
public:
  virtual ~Shape() = default;
  Shape();
  Shape(shared_ptr<Shader> shader);
  virtual bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const = 0;
  virtual BoundingBox boundingBox() const = 0;
  virtual point3 _center() const = 0;

protected:
  shared_ptr<Shader> shader;
};

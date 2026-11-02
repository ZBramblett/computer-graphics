#pragma once
#include "Shape.h"
#include <vector>


class BVHNode : public Shape
{

public:
  BVHNode(std::vector<std::shared_ptr<Shape>> shapes, int AXIS);
  bool intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const override;
  point3 _center() const override;
  BoundingBox boundingBox() const override;

private:
  std::shared_ptr<Shape> leftChild;
  std::shared_ptr<Shape> rightChild;
  BoundingBox bbox;
  BoundingBox mergeBoundingBoxes(const BoundingBox &b0, const BoundingBox &b1);
};
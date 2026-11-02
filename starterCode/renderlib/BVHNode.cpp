#include "BVHNode.h"
#include <algorithm>

BVHNode::BVHNode(std::vector<std::shared_ptr<Shape>> shapes, int AXIS)
{
  unsigned int N = shapes.size();

  if (N == 1) {
    leftChild = shapes[0];
    rightChild = nullptr;
    bbox = shapes[0]->boundingBox();
  } else if (N == 2) {
    leftChild = shapes[0];
    rightChild = shapes[1];
    bbox = mergeBoundingBoxes(shapes[0]->boundingBox(), shapes[1]->boundingBox());
  } else {
    std::sort(shapes.begin(), shapes.end(), [AXIS](const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
      return (a->_center()[AXIS] < b->_center()[AXIS]);
    });
  }

  std::vector<std::shared_ptr<Shape>> leftside(shapes.begin(), shapes.begin() + (N / 2));
  std::vector<std::shared_ptr<Shape>> rightside(shapes.begin() + (N / 2), shapes.end());

  leftChild = std::make_shared<BVHNode>(leftside, (AXIS + 1) % 3);
  rightChild = std::make_shared<BVHNode>(rightside, (AXIS + 1) % 3);

  bbox = mergeBoundingBoxes(leftChild->boundingBox(), rightChild->boundingBox());
}

bool BVHNode::intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const
{
  HitRecord lhit, rhit;
  if (bbox.hit(r, ray_tmin, ray_tmax)) {
    auto leftHit = leftChild->intersect(r, ray_tmin, ray_tmax, lhit);
    auto rightHit = rightChild && rightChild->intersect(r, ray_tmin, ray_tmax, rhit);

    if (leftHit && rightHit) {
      rec = (lhit.t < rhit.t) ? lhit : rhit;
      return true;
    } else if (leftHit) {
      rec = lhit;
      return true;
    } else if (rightHit) {
      rec = rhit;
      return true;
    }
  }
  return false;
}

point3 BVHNode::_center() const
{
  return (bbox.llb + bbox.urf) / 2;
}

BoundingBox BVHNode::boundingBox() const
{
  return bbox;
}

BoundingBox BVHNode::mergeBoundingBoxes(const BoundingBox &b0, const BoundingBox &b1)
{
  BoundingBox newBB = b0;
  newBB.update(b1.llb);
  newBB.update(b1.urf);
  return newBB;
}

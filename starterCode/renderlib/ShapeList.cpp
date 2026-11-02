#include "ShapeList.h"

ShapeList::ShapeList(shared_ptr<Shape> object) { add(object); }

void ShapeList::clear()
{
  objects.clear();
}

void ShapeList::add(shared_ptr<Shape> object)
{
  objects.push_back(object);
}

bool ShapeList::intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const
{
  HitRecord temp_rec;
  bool hit_anything = false;
  auto closest_so_far = ray_tmax;

  for (const auto &object : objects) {
    if (object->intersect(r, ray_tmin, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }
  return hit_anything;
}

BoundingBox ShapeList::boundingBox() const
{
  if (objects.empty()) {
    return BoundingBox();
  }
  BoundingBox bbox = objects[0]->boundingBox();

  for (const auto &object : objects) {
    bbox.update(object->boundingBox().llb);
    bbox.update(object->boundingBox().urf);
  }
  return bbox;
}

point3 ShapeList::_center() const
{
  BoundingBox bbox = boundingBox();
  return (bbox.llb + bbox.urf) / 2;
}

const std::vector<shared_ptr<Shape>> &ShapeList::getObjects() const
{
  return objects;
}
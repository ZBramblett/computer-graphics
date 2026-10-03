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

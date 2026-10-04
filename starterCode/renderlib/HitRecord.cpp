#include "HitRecord.h"

void HitRecord::setFaceNormal(const ray &r, const vec3 &outward_normal)
{
  normal = outward_normal;
  if (dot(r.direction(), normal) > 0) {
    normal = -normal;
  }
}
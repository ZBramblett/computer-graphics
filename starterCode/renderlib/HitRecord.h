#pragma once
#include "ray.h"
#include "vec3.h"

#include <memory>

using std::shared_ptr;

// forward declaration, we only hold a pointer so we don't need the full Shader here
class Shader;

struct HitRecord
{
  point3 p;
  vec3 normal;
  double t;
  shared_ptr<Shader> shader;
  void setFaceNormal(const ray &r, const vec3 &outward_normal);
};

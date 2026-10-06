#pragma once
#include "color.h"
#include "ray.h"
#include "HitRecord.h"
#include "Light.h"
#include <vector>
#include "Scene.h"

class Shader
{
public:
  virtual ~Shader() = default;
  Shader(color newColor);
  Shader() = default;
  virtual color shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights, const Scene &scene) const = 0;

protected:
  color baseColor = color(1, 0, 1);
};

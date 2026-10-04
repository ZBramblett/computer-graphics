#pragma once
#include "color.h"
#include "Shape.h"

class Shader
{
public:
  virtual ~Shader() = default;
  Shader(color newColor);
  Shader() = default;
  virtual color shade(const ray &r, const HitRecord &rec) const = 0;

protected:
  color baseColor = color(1, 0, 1);
};
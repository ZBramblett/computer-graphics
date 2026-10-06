#pragma once
#include "Shader.h"

class LambertianShader : public Shader
{
public:
  LambertianShader() = default;
  LambertianShader(color baseColor);
  color shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights, const Scene &scene) const override;
};
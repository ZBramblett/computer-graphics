#pragma once
#include "Shader.h"

class SolidColorShader : public Shader
{
public:
  SolidColorShader() = default;
  SolidColorShader(color baseColor);
  color shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights) const override;
};
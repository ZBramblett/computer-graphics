#pragma once

#include "Shader.h"

class BlinnPhongShader : public Shader
{
public:
  BlinnPhongShader() = default;
  BlinnPhongShader(color baseColor, color specularColor = color(1, 1, 1), double shininess = 32.0);
  color shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights) const override;

private:
  color specularColor = color(1, 1, 1);
  double shininess = 32.0;
};

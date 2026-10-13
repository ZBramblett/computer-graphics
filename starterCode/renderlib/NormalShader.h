#pragma once
#include "Shader.h"

class NormalShader : public Shader
{
public:
  NormalShader();
  color shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights, const Scene &scene, int depth) const override;
};

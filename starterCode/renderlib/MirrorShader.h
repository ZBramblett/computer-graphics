#pragma once

#include "Shader.h"

class MirrorShader : public Shader
{
public:
  MirrorShader() = default;
  MirrorShader(color baseColor);
  color shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights, const Scene &scene, int depth) const override;
};

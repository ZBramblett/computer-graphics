#include "NormalShader.h"

NormalShader::NormalShader() {}

color NormalShader::shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights, const Scene &scene, int depth) const
{
  return (rec.normal + vec3(1.0, 1.0, 1.0)) * 0.5;
}

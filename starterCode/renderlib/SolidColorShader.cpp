#include "SolidColorShader.h"
#include <vector>


SolidColorShader::SolidColorShader(color baseColor) : Shader(baseColor) {}

color SolidColorShader::shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights, const Scene &scene) const
{
  return baseColor;
}
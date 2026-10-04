#include "LambertianShader.h"
#include <algorithm>

LambertianShader::LambertianShader(color baseColor) : Shader(baseColor) {}

color LambertianShader::shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights) const
{
  color result = color(0,0,0);
  for (const auto &light : lights) {
    vec3 lightDir = light->calculateLightDirection(rec.p);
    double diff = std::max(0.0, dot(lightDir, rec.normal));
    result += baseColor * light->getRadiance() * diff;
  }
  for (int i = 0; i < 3; ++i) {
    result[i] = std::min(1.0, result[i]);
  }
  return result;
}
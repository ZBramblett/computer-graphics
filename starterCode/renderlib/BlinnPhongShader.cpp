#include "BlinnPhongShader.h"
#include <algorithm>
#include <cmath>

BlinnPhongShader::BlinnPhongShader(color baseColor, color specularColor, double shininess) : Shader(baseColor), specularColor(specularColor), shininess(shininess) {}

color BlinnPhongShader::shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights, const Scene &scene) const
{
  vec3 viewDir = unit_vector(-r.direction());
  color result = color(0, 0, 0);

  for (const auto &light : lights) {
    if (scene.isOccluded(light, rec)) {
      continue;
    }
    vec3 lightDir = light->calculateLightDirection(rec.p);
    double diff = std::max(0.0, dot(lightDir, rec.normal));
    vec3 halfDir = unit_vector(lightDir + viewDir);
    double spec = std::pow(std::max(0.0, dot(rec.normal, halfDir)), shininess);
    result += light->getRadiance() * (diff * baseColor + spec * specularColor);
  }

  for (int i = 0; i < 3; ++i) {
    result[i] = std::min(1.0, result[i]);
  }
  return result;
}

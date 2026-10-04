#include "SolidColorShader.h"


SolidColorShader::SolidColorShader(color baseColor) : Shader(baseColor) {}

color SolidColorShader::shade(const ray &r, const HitRecord &rec) const
{
  return baseColor;
}
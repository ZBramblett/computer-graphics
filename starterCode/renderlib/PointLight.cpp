#include "PointLight.h"


PointLight::PointLight(color lightColor, double intensity, point3 p) : Light(lightColor, intensity), position(p) {}

vec3 PointLight::calculateLightDirection(point3 p) const
{
  return unit_vector(position - p);
}

#include "Light.h"

Light::Light(color lightColor, double intensity) : lightColor(lightColor), intensity(intensity) {}

color Light::getRadiance() const
{
  return lightColor * intensity;
}

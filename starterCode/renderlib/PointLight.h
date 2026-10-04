#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
  PointLight(color lightColor, double intensity, point3 p);
  vec3 calculateLightDirection(point3 p) const override;

private:
  point3 position;
};
#pragma once

#include "color.h"


class Light
{
public:
  virtual ~Light() = default;
  virtual vec3 calculateLightDirection(point3 p) const = 0;
  virtual double getDistance(point3 p) const = 0;
  Light() = default;
  Light(color lightColor, double intensity);
  color getRadiance() const;


protected:
  double intensity = 1.0;
  color lightColor = color(1, 1, 1);
};
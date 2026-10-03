#pragma once

#include "ray.h"

class Camera
{
public:
  Camera(vec3 viewdir, point3 origin, int height, int width, double imagePlaneWidth);
  virtual ~Camera() = default;
  virtual void generateRay(int i, int j, ray &myRay) const = 0;

protected:
  vec3 U, V, W;
  point3 origin;
  int height, width;
  double imagePlaneWidth, imagePlaneHeight;
  double l, r, b, t;
};

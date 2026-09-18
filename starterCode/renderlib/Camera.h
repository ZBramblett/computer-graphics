#pragma once

#include "ray.h"

class Camera
{
public:
  Camera(vec3 U, vec3 V, vec3 W, vec3 E, double l, double r, double b, double t, int height, int width) : U(U), V(V), W(W), E(E), l(l), r(r), b(b), t(t), height(height), width(width) {}

  virtual ~Camera() = default;

  virtual void generateRay(int i, int j, ray &myRay) const = 0;

protected:
  vec3 U, V, W, E;
  int height, width;
  double l, r, b, t;
};

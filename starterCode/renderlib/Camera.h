#pragma once

#include "ray.h"

class Camera
{
public:
  Camera(vec3 viewdir, point3 origin, int height, int width, double imagePlaneWidth);
  virtual ~Camera() = default;
  virtual void generateRay(double i, double j, ray &myRay) const = 0;

  // View matrix data
  const point3 &getOrigin() const { return origin; }
  const vec3 &getU() const { return U; }
  const vec3 &getV() const { return V; }
  const vec3 &getW() const { return W; }

  // Image plane bounds (for the projection matrix)
  double getLeft() const { return l; }
  double getRight() const { return r; }
  double getBottom() const { return b; }
  double getTop() const { return t; }

protected:
  vec3 U, V, W;
  point3 origin;
  int height, width;
  double imagePlaneWidth, imagePlaneHeight;
  double l, r, b, t;
};

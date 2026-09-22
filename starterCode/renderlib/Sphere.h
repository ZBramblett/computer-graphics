#pragma once
#include "Shape.h"

class Sphere : Shape
{
public:
  Sphere(point3 sphereCenter, double sphereRadius) : center(sphereCenter), radius(sphereRadius) {}

  bool intersect(const ray &r)
  {
    vec3 d = r.direction();
    point3 e = r.origin();
    vec3 oc = e - center;
    vec3 d2 = 2 * d;
    double rSquared = radius * radius;

    double A = dot(d, d);
    double B = dot(d2, oc);
    double C = dot(oc, oc) - rSquared;

    double discriminant = (B * B) - 4 * (A * C);
    // checking the discriminant
    if (discriminant < 0) {
      return false;
    } else {
      return true;
    }
  }

protected:
  double radius;
  point3 center;
};
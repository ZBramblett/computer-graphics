#include "Sphere.h"

Sphere::Sphere(point3 sphereCenter, double sphereRadius, shared_ptr<Shader> shader) : Shape(shader), center(sphereCenter), radius(sphereRadius) {}

bool Sphere::intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const
{
  // setting up my variables
  vec3 d = r.direction();
  point3 e = r.origin();
  vec3 oc = e - center;
  vec3 d2 = 2 * d;
  double rSquared = radius * radius;
  // find A B & C for quadratic equation
  double A = dot(d, d);
  double B = dot(d2, oc);
  double C = dot(oc, oc) - rSquared;
  // finding the discriminant
  double discriminant = (B * B) - (4 * A * C);
  // checking the discriminant
  if (discriminant < 0) {
    return false;
  }

  // nearest root first, then the far one if the near one is outside the window
  double sqrtd = std::sqrt(discriminant);
  double root = (-B - sqrtd) / (2 * A);
  if (root <= ray_tmin || root >= ray_tmax) {
    root = (-B + sqrtd) / (2 * A);
    if (root <= ray_tmin || root >= ray_tmax) {
      return false;
    }
  }

  // fill in the hit record for whoever called us
  rec.t = root;
  rec.p = r.at(root);
  rec.setFaceNormal(r, (rec.p - center) / radius);
  rec.shader = shader;
  return true;
}

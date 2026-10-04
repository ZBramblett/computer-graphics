#include "Triangle.h"

Triangle::Triangle(point3 a, point3 b, point3 c, shared_ptr<Shader> shader) : Shape(shader), a(a), b(b), c(c) {}


bool Triangle::intersect(const ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const
{
  // setup Cramer's rule
  double A = (a.x() - b.x());
  double B = (a.y() - b.y());
  double C = (a.z() - b.z());

  double D = (a.x() - c.x());
  double E = (a.y() - c.y());
  double F = (a.z() - c.z());

  double G = r.direction().x();
  double H = r.direction().y();
  double I = r.direction().z();

  double J = (a.x() - r.origin().x());
  double K = (a.y() - r.origin().y());
  double L = (a.z() - r.origin().z());

  double EIHF = E * I - H * F;
  double GFDI = G * F - D * I;
  double DHEG = D * H - E * G;
  double AKJB = A * K - J * B;
  double JCAL = J * C - A * L;
  double BLKC = B * L - K * C;


  double M = A * EIHF + B * GFDI + C * DHEG;
  double Beta = (J * EIHF + K * GFDI + L * DHEG) / M;
  double Gamma = (I * AKJB + H * JCAL + G * BLKC) / M;
  double t = -(F * AKJB + E * JCAL + D * BLKC) / M;

  if (Beta > 0 && Gamma > 0 && Beta + Gamma < 1 && t > ray_tmin && t < ray_tmax) {
    rec.t = t;
    rec.p = r.at(t);
    rec.setFaceNormal(r, unit_vector(cross((b - a), (c - a))));
    rec.shader = shader;
    return true;
  }
  return false;
}
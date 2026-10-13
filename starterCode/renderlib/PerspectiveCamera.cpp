#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(vec3 viewdir, point3 origin, int height, int width, double imagePlaneWidth, double focalLength) : Camera(viewdir, origin, height, width, imagePlaneWidth), focalLength(focalLength) {}

void PerspectiveCamera::generateRay(double i, double j, ray &myRay) const
{
  double u = l + (r - l) * (i) / width;
  double v = b + (t - b) * (j) / height;
  vec3 direction = -focalLength * W + u * U + v * V;
  myRay = ray(origin, direction);
}
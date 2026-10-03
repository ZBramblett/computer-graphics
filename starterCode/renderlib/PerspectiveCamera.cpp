#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(vec3 viewdir, point3 origin, int height, int width, double imagePlaneWidth, double focalLength) : Camera(viewdir, origin, height, width, imagePlaneWidth), focalLength(focalLength) {}

void PerspectiveCamera::generateRay(int i, int j, ray &myRay) const
{
  double u = l + (r - l) * (i + 0.5) / width;
  double v = b + (t - b) * (j + 0.5) / height;
  vec3 direction = -focalLength * W + u * U + v * V;
  myRay = ray(origin, direction);
}
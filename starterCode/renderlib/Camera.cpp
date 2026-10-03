#include "Camera.h"

Camera::Camera(vec3 viewdir, point3 origin, int height, int width, double imagePlaneWidth) : origin(origin), height(height), width(width), imagePlaneWidth(imagePlaneWidth)
{
  W = unit_vector(-viewdir);
  U = unit_vector(cross(vec3(0, 1, 0), W));
  V = cross(W, U);

  imagePlaneHeight = imagePlaneWidth * (double)height / width;

  l = -imagePlaneWidth / 2;
  r = imagePlaneWidth / 2;
  b = -imagePlaneHeight / 2;
  t = imagePlaneHeight / 2;
}
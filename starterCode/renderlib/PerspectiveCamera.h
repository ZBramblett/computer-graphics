#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(vec3 viewdir, point3 origin, int height, int width, double imagePlaneWidth, double focalLength);
  void generateRay(int i, int j, ray &myRay) const override;

private:
  double focalLength;
};

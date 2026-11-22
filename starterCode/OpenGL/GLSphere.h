#pragma once

#include "glm/glm.hpp"

#include "GLShape.h"

// one sphere made from a subdivided icosahedron
class GLSphere : public GLShape
{
public:
  // builds the sphere and puts it on the gpu
  GLSphere(const glm::vec3 &center, float radius, int subdivisions = 3);
};

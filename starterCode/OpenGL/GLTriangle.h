#pragma once

#include "glm/glm.hpp"

#include "GLShape.h"

// one triangle
class GLTriangle : public GLShape
{
public:
  // builds the triangle and puts it on the gpu
  GLTriangle(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C);
};

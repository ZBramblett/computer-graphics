#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "GLShape.h"

// lots of triangles in one buffer
class GLTriangleMesh : public GLShape
{
public:
  // builds the mesh and puts it on the gpu, every 3 points is one triangle
  GLTriangleMesh(const std::vector<glm::vec3> &points);
};

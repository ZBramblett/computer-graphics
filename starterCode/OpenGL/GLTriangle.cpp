#include "GLTriangle.h"

GLTriangle::GLTriangle(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C)
{
  glm::vec3 triNormal = glm::normalize(glm::cross(B - A, C - A));

  // clang-format off
  std::vector<float> vertices{
    A.x, A.y, A.z, triNormal.x, triNormal.y, triNormal.z,
    B.x, B.y, B.z, triNormal.x, triNormal.y, triNormal.z,
    C.x, C.y, C.z, triNormal.x, triNormal.y, triNormal.z,
  };
  // clang-format on

  uploadVertices(vertices);
}

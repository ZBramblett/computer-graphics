#include "GLTriangleMesh.h"

GLTriangleMesh::GLTriangleMesh(const std::vector<glm::vec3> &points)
{
  std::vector<float> vertices;
  vertices.reserve(points.size() * 6);

  for (size_t i = 0; i + 2 < points.size(); i += 3) {
    const glm::vec3 &A = points[i];
    const glm::vec3 &B = points[i + 1];
    const glm::vec3 &C = points[i + 2];

    glm::vec3 triNormal = glm::normalize(glm::cross(B - A, C - A));

    // clang-format off
    vertices.insert(vertices.end(), {
      A.x, A.y, A.z, triNormal.x, triNormal.y, triNormal.z,
      B.x, B.y, B.z, triNormal.x, triNormal.y, triNormal.z,
      C.x, C.y, C.z, triNormal.x, triNormal.y, triNormal.z,
    });
    // clang-format on
  }

  uploadVertices(vertices);
}

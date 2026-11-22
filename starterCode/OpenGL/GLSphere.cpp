#include "GLSphere.h"

#include <cmath>

GLSphere::GLSphere(const glm::vec3 &center, float radius, int subdivisions)
{
  // the 12 corners of an icosahedron
  float t = (1.0f + std::sqrt(5.0f)) / 2.0f;
  // clang-format off
  std::vector<glm::vec3> corners{
    { -1, t, 0 }, { 1, t, 0 }, { -1, -t, 0 }, { 1, -t, 0 },
    { 0, -1, t }, { 0, 1, t }, { 0, -1, -t }, { 0, 1, -t },
    { t, 0, -1 }, { t, 0, 1 }, { -t, 0, -1 }, { -t, 0, 1 }
  };
  // clang-format on

  // the 20 faces, as corner numbers
  // clang-format off
  int faces[20][3] = {
    { 0, 11, 5 }, { 0, 5, 1 },  { 0, 1, 7 },   { 0, 7, 10 }, { 0, 10, 11 },
    { 1, 5, 9 },  { 5, 11, 4 }, { 11, 10, 2 }, { 10, 7, 6 }, { 7, 1, 8 },
    { 3, 9, 4 },  { 3, 4, 2 },  { 3, 2, 6 },   { 3, 6, 8 },  { 3, 8, 9 },
    { 4, 9, 5 },  { 2, 4, 11 }, { 6, 2, 10 },  { 8, 6, 7 },  { 9, 8, 1 }
  };
  // clang-format on

  // every 3 points is one triangle, all on the unit sphere
  std::vector<glm::vec3> triangles;
  for (auto &face : faces) {
    triangles.push_back(glm::normalize(corners[face[0]]));
    triangles.push_back(glm::normalize(corners[face[1]]));
    triangles.push_back(glm::normalize(corners[face[2]]));
  }

  // splits every triangle into 4
  for (int round = 0; round < subdivisions; ++round) {
    std::vector<glm::vec3> smaller;
    for (size_t i = 0; i < triangles.size(); i += 3) {
      glm::vec3 a = triangles[i];
      glm::vec3 b = triangles[i + 1];
      glm::vec3 c = triangles[i + 2];

      // edge midpoints pushed out to the sphere
      glm::vec3 ab = glm::normalize(a + b);
      glm::vec3 bc = glm::normalize(b + c);
      glm::vec3 ca = glm::normalize(c + a);

      smaller.insert(smaller.end(), { a, ab, ca });
      smaller.insert(smaller.end(), { b, bc, ab });
      smaller.insert(smaller.end(), { c, ca, bc });
      smaller.insert(smaller.end(), { ab, bc, ca });
    }
    triangles = smaller;
  }

  // moves to the real center and size, normal is the unit point
  std::vector<float> vertices;
  vertices.reserve(triangles.size() * 6);
  for (const glm::vec3 &p : triangles) {
    glm::vec3 pos = center + radius * p;
    vertices.insert(vertices.end(), { pos.x, pos.y, pos.z, p.x, p.y, p.z });
  }

  uploadVertices(vertices);
}

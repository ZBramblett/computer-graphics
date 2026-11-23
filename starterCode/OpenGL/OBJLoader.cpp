#include "OBJLoader.h"

#include <iostream>

#include "model_obj.h"

std::vector<glm::vec3> loadOBJ(const std::string &filename)
{
  std::vector<glm::vec3> points;

  ModelOBJ model;
  if (!model.import(filename.c_str())) {
    std::cerr << "could not load obj file: " << filename << std::endl;
    return points;
  }

  // the index buffer says which 3 vertices make each triangle
  const int *indices = model.getIndexBuffer();
  int numIndices = model.getNumberOfTriangles() * 3;
  points.reserve(numIndices);

  for (int i = 0; i < numIndices; ++i) {
    const ModelOBJ::Vertex &v = model.getVertex(indices[i]);
    points.push_back(glm::vec3(v.position[0], v.position[1], v.position[2]));
  }

  std::cout << "loaded " << model.getNumberOfTriangles() << " triangles from " << filename << std::endl;
  return points;
}

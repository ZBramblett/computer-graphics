#pragma once

#include <string>
#include <vector>

#include "glm/glm.hpp"

// reads an obj file and returns its triangle points, every 3 points is one triangle
std::vector<glm::vec3> loadOBJ(const std::string &filename);

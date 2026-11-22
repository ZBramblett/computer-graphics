#pragma once

#include <vector>

#include <GL/glew.h>

// Base class for anything drawn with OpenGL.
class GLShape
{
public:
  GLShape() = default;
  virtual ~GLShape();

  GLShape(const GLShape &) = delete;
  GLShape &operator=(const GLShape &) = delete;

  void draw() const;

protected:
  // Copies the floats to the GPU and describes their layout in the VAO
  void uploadVertices(const std::vector<float> &vertices);

  GLuint m_VAO = 0;// 0 means "not created yet"
  GLuint m_VBO = 0;
  GLsizei m_vertexCount = 0;
};

#include "GLShape.h"

GLShape::~GLShape()
{
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}

void GLShape::uploadVertices(const std::vector<float> &vertices)
{
  m_vertexCount = vertices.size() / 6;
  int numBytes = vertices.size() * sizeof(float);

  // create one Vertex Buffer Object (VBO) to hold positions and normals together
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  // copy the floats to the GPU and store them in the currently bound VBO
  glBufferData(GL_ARRAY_BUFFER, numBytes, vertices.data(), GL_STATIC_DRAW);

  // create a vertex array object that maps the attributes in the vertex buffer to the location attributes in the shaders
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  GLsizei stride = 6 * sizeof(GLfloat);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(GLfloat)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLShape::draw() const
{
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
  glBindVertexArray(0);
}

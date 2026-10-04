#include "Shape.h"
#include "SolidColorShader.h"
#include <memory>

using std::make_shared;

Shape::Shape() : shader(make_shared<SolidColorShader>()) {}
Shape::Shape(shared_ptr<Shader> shader) : shader(shader)
{
  if (!shader) {
    this->shader = make_shared<SolidColorShader>();
  }
}
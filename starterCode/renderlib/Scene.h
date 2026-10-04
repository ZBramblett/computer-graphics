#pragma once

#include "Camera.h"
#include "ShapeList.h"
#include "Framebuffer.h"

class Scene
{
public:
  void setCamera(shared_ptr<Camera> camera);
  void addShape(shared_ptr<Shape> shape);
  shared_ptr<Camera> getCamera() const;
  const ShapeList &getWorld() const;
  void renderScene(Framebuffer &fb) const;

private:
  shared_ptr<Camera> camera;
  ShapeList world;

  color findRayColor(const ray &r) const;
};
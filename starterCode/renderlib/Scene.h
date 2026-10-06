#pragma once

#include "Camera.h"
#include "ShapeList.h"
#include "Framebuffer.h"
#include "Light.h"

class Scene
{
public:
  void setCamera(shared_ptr<Camera> camera);
  void addShape(shared_ptr<Shape> shape);
  void addLight(shared_ptr<Light> light);
  shared_ptr<Camera> getCamera() const;
  const ShapeList &getWorld() const;
  void renderScene(Framebuffer &fb) const;
  bool isOccluded(shared_ptr<Light> light, const HitRecord &rec) const;

private:
  shared_ptr<Camera> camera;
  ShapeList world;
  std::vector<shared_ptr<Light>> lights;
  color findRayColor(const ray &r) const;
};
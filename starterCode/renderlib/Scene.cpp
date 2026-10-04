#include "Scene.h"
#include "rtweekend.h"
#include "Shader.h"

void Scene::setCamera(shared_ptr<Camera> camera)
{
  this->camera = camera;
}
void Scene::addShape(shared_ptr<Shape> shape)
{
  world.add(shape);
}

shared_ptr<Camera> Scene::getCamera() const
{
  return camera;
}
const ShapeList &Scene::getWorld() const
{
  return world;
}
void Scene::renderScene(Framebuffer &fb) const
{
  for (int x = 0; x < fb.getWidth(); ++x) {
    for (int y = 0; y < fb.getHeight(); ++y) {
      ray r;
      camera->generateRay(x, y, r);
      color pixel_color = findRayColor(r);
      fb.setPixelColor(x, y, pixel_color);
    }
  }
}
void Scene::addLight(shared_ptr<Light> light)
{
  lights.push_back(light);
}

color Scene::findRayColor(const ray &r) const
{
  HitRecord rec;
  if (world.intersect(r, 0, infinity, rec)) {
    return rec.shader->shade(r, rec, lights);
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
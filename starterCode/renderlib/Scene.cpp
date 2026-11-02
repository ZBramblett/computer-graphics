#include "Scene.h"
#include "rtweekend.h"
#include "Shader.h"
#include <algorithm>

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

// Modify to get anti-aliasing (Do the grid one from the slides)
void Scene::renderScene(Framebuffer &fb, int rpp) const
{
  // the grid is N x N, so use the closest whole N to get about rpp rays per pixel
  int rpp_Nsquare = static_cast<int>(std::round(std::sqrt(std::max(rpp, 1))));

#pragma omp parallel for
  for (int x = 0; x < fb.getWidth(); ++x) {
    for (int y = 0; y < fb.getHeight(); ++y) {
      color c(0.0, 0.0, 0.0);

      for (int p = 0; p < rpp_Nsquare; ++p) {
        for (int q = 0; q < rpp_Nsquare; ++q) {
          double pOffset = (p + randomOffset()) / rpp_Nsquare;
          double qOffset = (q + randomOffset()) / rpp_Nsquare;
          ray r;
          camera->generateRay(x + pOffset, y + qOffset, r);
          c += findRayColor(r, 5);
        }
      }
      c /= (rpp_Nsquare * rpp_Nsquare);
      fb.setPixelColor(x, y, c);
    }
  }
}
void Scene::addLight(shared_ptr<Light> light)
{
  lights.push_back(light);
}

bool Scene::isOccluded(shared_ptr<Light> light, const HitRecord &rec) const
{
  HitRecord occRec;
  ray r(rec.p, light->calculateLightDirection(rec.p));
  return (world.intersect(r, 0.0001, light->getDistance(rec.p), occRec));
}

color Scene::findRayColor(const ray &r, int depth) const
{

  if (depth <= 0) {
    return color(0, 0, 0);
  }
  HitRecord rec;
  if (world.intersect(r, 0.0001, infinity, rec)) {
    return rec.shader->shade(r, rec, lights, *this, depth);
  }

  // vec3 unit_direction = unit_vector(r.direction());
  // auto a = 0.5 * (unit_direction.y() + 1.0);
  // return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  return color(.5, .7, 1.0);
}

void Scene::buildBVH()
{
  if (world.getObjects().empty()) {
    return;
  }
  root = std::make_shared<BVHNode>(world.getObjects(), 0);
  world.clear();
  world.add(root);
}
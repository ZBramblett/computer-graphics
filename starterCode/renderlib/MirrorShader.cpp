#include "MirrorShader.h"
#include "Scene.h"

MirrorShader::MirrorShader(color baseColor) : Shader(baseColor) {}

color MirrorShader::shade(const ray &r, const HitRecord &rec, const std::vector<shared_ptr<Light>> &lights, const Scene &scene, int depth) const
{
  vec3 d = unit_vector(r.direction());
  vec3 n = rec.normal;
  vec3 reflectedDir = d - 2 * (dot(d, n)) * n;

  ray reflectedRay(rec.p + .0001 * n, reflectedDir);

  return scene.findRayColor(reflectedRay, depth - 1);
}
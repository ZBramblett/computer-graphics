#include "rtweekend.h"

#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "Sphere.h"
#include "ShapeList.h"

color ray_color(const ray &r, const Shape &world)
{
  HitRecord rec;
  if (world.intersect(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + color(1, 1, 1));
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
  Framebuffer fb(200, 200);
  vec3 viewdir(0, 0, -1);
  point3 origin(0, 0, 0);
  double imagePlaneWidth = 2;
  double focalLength = 1;
  PerspectiveCamera p(viewdir, origin, fb.getHeight(), fb.getWidth(), imagePlaneWidth, focalLength);

  ShapeList world;

  world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));
  world.add(make_shared<Sphere>(point3(-2, 0, -2), 0.5));
  world.add(make_shared<Sphere>(point3(2, 0, -2), 0.5));

  for (int x = 0; x < fb.getWidth(); ++x) {
    for (int y = 0; y < fb.getHeight(); ++y) {
      ray r;
      p.generateRay(x, y, r);

      color pixel_color = ray_color(r, world);
      fb.setPixelColor(x, y, pixel_color);
    }
  }

  fb.exportToPNG("generated_image.png");
};


// Code for cosine waves
//  color one(23, 6, 209);
//  color two(199, 6, 48);

// for (int x = 0; x < 1600; ++x) {
//   for (int y = 0; y < 900; ++y) {
//     ray r;
//     p.generateRay(x, y, r);
//     vec3 direction = unit_vector(r.direction());

//     double frequency = direction.y() * 30;
//     double stripes = std::cos(frequency);
//     color ray_dir_color;

//     if (stripes > 0) {
//       ray_dir_color = normalizeColor(one);
//     } else {
//       ray_dir_color = normalizeColor(two);
//     }
//   }
// }

// Code for ray to color stuff
//  for (int x = 0; x < 1600; ++x) {
//    for (int y = 0; y < 900; ++y) {
//      ray r;
//      p.generateRay(x, y, r);
//      vec3 direction = unit_vector(r.direction());
//      color ray_dir_color = 0.5 * (direction + vec3(1, 1, 1));
//     fb.setPixelColor(x, y, ray_dir_color);
//   }
// }

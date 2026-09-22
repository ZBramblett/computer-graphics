#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "color.h"
#include "Sphere.h"


int main()
{
  Framebuffer fb(1600, 900);
  vec3 viewdir(0, 0, -1);
  point3 origin(0, 0, 0);
  double imagePlaneWidth = 2;
  double focalLength = 1;
  PerspectiveCamera p(viewdir, origin, fb.getHeight(), fb.getWidth(), imagePlaneWidth, focalLength);
  point3 sphereCenter(0, 0, -3);
  double sphereRadius = 1.0;

  Sphere s(sphereCenter, sphereRadius);

  color sphere(188, 0, 45);
  color background(255, 255, 255);

  for (int x = 0; x < fb.getWidth(); ++x) {
    for (int y = 0; y < fb.getHeight(); ++y) {
      ray r;
      p.generateRay(x, y, r);

      if (s.intersect(r)) {
        fb.setPixelColor(x, y, normalizeColor(sphere));
      } else {
        fb.setPixelColor(x, y, normalizeColor(background));
      }
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

//     color ray_dir_color = vec3(brightness, brightness, brightness);

//     fb.setPixelColor(x, y, ray_dir_color);
//   }
// }

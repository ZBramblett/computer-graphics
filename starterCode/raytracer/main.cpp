#include "rtweekend.h"

#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "Sphere.h"
#include "Triangle.h"
#include "ShapeList.h"
#include "Scene.h"


int main()
{
  Framebuffer fb(200, 200);
  vec3 viewdir(0, 0, -1);
  point3 origin(0, 0, 0);
  double imagePlaneWidth = .5;
  double focalLength = 1;
  auto p = make_shared<PerspectiveCamera>(viewdir, origin, fb.getHeight(), fb.getWidth(), imagePlaneWidth, focalLength);

  Scene scene;
  scene.setCamera(p);
  scene.addShape(make_shared<Triangle>(point3(-1.2, -0.2, -7), point3(.8, -0.5, -5), point3(0.9, 0, -5), color(1, 0, 0)));
  scene.addShape(make_shared<Triangle>(point3(0.773205, -0.93923, -7), point3(0.0330127, 0.94282, -5), point3(-0.45, 0.779423, -5), color(0, 1, 0)));
  scene.addShape(make_shared<Triangle>(point3(0.426795, 1.13923, -7), point3(-0.833013, -0.44282, -5), point3(-0.45, -0.779423, -5), color(0, 0, 1)));

  scene.renderScene(fb);


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

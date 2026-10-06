#include "rtweekend.h"

#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "Sphere.h"
#include "Triangle.h"
#include "ShapeList.h"
#include "Scene.h"
#include "SolidColorShader.h"
#include "LambertianShader.h"
#include "BlinnPhongShader.h"
#include "PointLight.h"


int main()
{
  Framebuffer fb(2000, 2000);
  vec3 viewdir(0, -0.3, -1);
  point3 origin(0, 2, 1);
  double imagePlaneWidth = 1;
  double focalLength = 1;
  auto p = make_shared<PerspectiveCamera>(viewdir, origin, fb.getHeight(), fb.getWidth(), imagePlaneWidth, focalLength);


  // colors & shaders
  color sphereColor(0, 0.8, 0.8);
  auto matte = make_shared<LambertianShader>(sphereColor);
  auto satin = make_shared<BlinnPhongShader>(sphereColor, color(0.6, 0.6, 0.6), 16);
  auto glossy = make_shared<BlinnPhongShader>(sphereColor, color(1, 1, 1), 200);

  auto floorShader = make_shared<LambertianShader>(color(0.5, 0.5, 0.5));
  // lights
  auto warmLight = make_shared<PointLight>(color(1.0, 0.85, 0.7), 0.8, point3(4, 4, 0));
  auto coolLight = make_shared<PointLight>(color(0.4, 0.6, 1.0), 0.35, point3(-4, 2, -1));

  Scene scene;
  scene.setCamera(p);
  scene.addLight(warmLight);
  scene.addLight(coolLight);
  // floor
  scene.addShape(make_shared<Sphere>(point3(0, -100.5, -5), 100, floorShader));
  // 3 balls
  scene.addShape(make_shared<Sphere>(point3(-1.2, 0, -4), 0.5, matte));
  scene.addShape(make_shared<Sphere>(point3(0, 0, -4), 0.5, satin));
  scene.addShape(make_shared<Sphere>(point3(1.2, 0, -4), 0.5, glossy));


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

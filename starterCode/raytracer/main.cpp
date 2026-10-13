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
#include "NormalShader.h"
#include "PointLight.h"
#include "MirrorShader.h"


int main()
{
  Framebuffer fb(500, 500);
  vec3 viewdir(0, -0.4, -1);
  point3 origin(0, 3, 3);
  double imagePlaneWidth = .5;
  double focalLength = .4;
  auto p = make_shared<PerspectiveCamera>(viewdir, origin, fb.getHeight(), fb.getWidth(), imagePlaneWidth, focalLength);

  // Lights
  auto Light1 = make_shared<PointLight>(color(.7, .6, .45), 1.0, point3(-5, 8, 5));
  auto Light2 = make_shared<PointLight>(color(.35, .45, .7), 1.0, point3(6, 6, 2));

  // Floor
  auto diffuseGrey = make_shared<LambertianShader>(color(.6, .6, .6));

  auto ground1 = make_shared<Triangle>(point3(-50, 0, 50), point3(50, 0, 50), point3(50, 0, -50), diffuseGrey);
  auto ground2 = make_shared<Triangle>(point3(-50, 0, 50), point3(50, 0, -50), point3(-50, 0, -50), diffuseGrey);

  // Mirror Wall
  auto mirrorShader = make_shared<MirrorShader>(color(1, 1, 1));
  auto wall1 = make_shared<Triangle>(point3(-4, 0, -6), point3(4, 0, -6), point3(4, 4, -6), mirrorShader);
  auto wall2 = make_shared<Triangle>(point3(-4, 0, -6), point3(4, 4, -6), point3(-4, 5, -6), mirrorShader);

  // Floating Triangle
  auto diffuseYellow = make_shared<LambertianShader>(color(.9, .8, .1));
  auto floatingTriangle = make_shared<Triangle>(point3(.9, 1.4, -0.6), point3(1.9, 1.4, -0.6), point3(1.4, 2.2, -1.1), diffuseYellow);

  // Spheres
  auto diffuseGreen = make_shared<LambertianShader>(color(.2, .8, .2));
  auto greenSphere = make_shared<Sphere>(point3(-2, .8, -3), .8, diffuseGreen);

  auto diffuseRed = make_shared<BlinnPhongShader>(color(.8, .1, .1), color(1, 1, 1), 64.0);
  auto redSphere = make_shared<Sphere>(point3(-1.1, .6, -1.2), .6, diffuseRed);

  auto normalShader = make_shared<NormalShader>();
  auto normalSphere = make_shared<Sphere>(point3(0, .9, -3.5), .9, normalShader);

  auto diffuseBlue = make_shared<BlinnPhongShader>(color(.1, .2, .8), color(1, 1, 1), 16.0);
  auto blueSphere = make_shared<Sphere>(point3(.3, .45, -1.6), .45, diffuseBlue);

  auto mirrorSphere = make_shared<Sphere>(point3(2, 1, -3), 1.0, mirrorShader);
  auto frontMirrorSphere = make_shared<Sphere>(point3(1.5, .5, .3), .5, mirrorShader);

  // Behind camera
  auto diffuseOrange = make_shared<BlinnPhongShader>(color(.95, .5, .1), color(1, 1, 1), 32.0);
  auto orangeSphere = make_shared<Sphere>(point3(0.3, 1, 5), 1, diffuseOrange);

  auto diffusePurple = make_shared<LambertianShader>(color(.6, .2, .8));
  auto purpleSphere = make_shared<Sphere>(point3(2.4, .8, 4.8), 0.8, diffusePurple);


  Scene scene;
  scene.setCamera(p);
  scene.addLight(Light1);
  scene.addLight(Light2);
  scene.addShape(ground1);
  scene.addShape(ground2);
  scene.addShape(wall1);
  scene.addShape(wall2);
  scene.addShape(floatingTriangle);
  scene.addShape(greenSphere);
  scene.addShape(redSphere);
  scene.addShape(normalSphere);
  scene.addShape(blueSphere);
  scene.addShape(mirrorSphere);
  scene.addShape(frontMirrorSphere);
  scene.addShape(orangeSphere);
  scene.addShape(purpleSphere);

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

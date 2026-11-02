#include "rtweekend.h"

#include "Framebuffer.h"
#include "Scene.h"
#include "SceneParser_JSON.h"
#include "SceneLoader.h"
#include <handleGraphicsArgs.h>


int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.width = 500;
  args.height = 500;
  args.rpp = 1;
  args.process(argc, argv);
  Framebuffer fb(args.width, args.height);
  Scene scene;

  std::shared_ptr<ISceneLoader> loader = std::make_shared<SceneLoader>(scene, fb.getWidth(), fb.getHeight());
  SceneParser_JSON parser(loader);

  std::string filename = args.inputFileName;
  parser.parseFileData(filename);

  printf("Rendering... please stand by");
  scene.renderScene(fb, args.rpp);

  std::string outName = args.outputFileName.empty() ? "default_image_name.png" : args.outputFileName;
  fb.exportToPNG(outName);
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

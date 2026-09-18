#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"


int main()
{
  Framebuffer fb(800, 800);
  vec3 viewdir(0, 0, -1);
  point3 origin(0, 0, 0);
  double imagePlaneWIdth = 2.0;
  double focalLength = 1.0;
  PerspectiveCamera p(viewdir, origin, fb.getHeight(), fb.getWidth(), imagePlaneWIdth, focalLength);

  for (int x = 0; x < 800; ++x) {
    for (int y = 0; y < 800; ++y) {
      ray r;
      p.generateRay(x, y, r);
      vec3 direction = unit_vector(r.direction());
      color ray_dir_color = 0.5 * (direction + vec3(1, 1, 1));

      fb.setPixelColor(x, y, ray_dir_color);
    }
  }

  fb.exportToPNG("8HoursOfWork.png");
};
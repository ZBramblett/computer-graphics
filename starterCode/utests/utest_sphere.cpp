#include <catch2/catch_test_macros.hpp>

#include "rtweekend.h"

#include "Sphere.h"

TEST_CASE("Testing a ray that hits the sphere")
{
  Sphere mySphere = Sphere(point3(0, 0, -5), 1);
  ray myRay = ray(point3(0, 0, 0), vec3(0, 0, -1));
  HitRecord rec;

  REQUIRE(mySphere.intersect(myRay, 0, infinity, rec) == true);
  REQUIRE(rec.t == 4);
}

TEST_CASE("Testing a ray that misses the sphere")
{
  Sphere mySphere = Sphere(point3(0, 0, -5), 1);
  ray myRay = ray(point3(0, 0, 0), vec3(0, 1, 0));
  HitRecord rec;

  REQUIRE(mySphere.intersect(myRay, 0, infinity, rec) == false);
}

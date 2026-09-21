#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include "ray.h"


TEST_CASE("Testing Ray Creation and variables")
{
  point3 origin = point3(1, 2, 3);
  vec3 direction = vec3(4, 5, 6);
  ray myRay = ray(origin, direction);

  REQUIRE(myRay.origin().x() == 1);
  REQUIRE(myRay.origin().y() == 2);
  REQUIRE(myRay.origin().z() == 3);

  REQUIRE(myRay.direction().x() == 4);
  REQUIRE(myRay.direction().y() == 5);
  REQUIRE(myRay.direction().z() == 6);
}
TEST_CASE("Testing the at function")
{

  ray myRay = ray(point3(1, 2, 3), vec3(4, 5, 6));

  // t = 0 lands right on the origin
  point3 start = myRay.at(0);

  REQUIRE(start.x() == 1);
  REQUIRE(start.y() == 2);
  REQUIRE(start.z() == 3);

  // t = 1 lands at origin + direction
  point3 t1 = myRay.at(1);

  REQUIRE(t1.x() == 5);
  REQUIRE(t1.y() == 7);
  REQUIRE(t1.z() == 9);

  // t = 2 lands at origin + 2 * direction
  point3 t2 = myRay.at(2);

  REQUIRE(t2.x() == 9);
  REQUIRE(t2.y() == 12);
  REQUIRE(t2.z() == 15);
}

TEST_CASE("Testing to make sure AT does not change the ray")
{

  ray myRay = ray(point3(1, 2, 3), vec3(4, 5, 6));

  point3 myPoint = myRay.at(5);

  REQUIRE(myRay.origin().x() == 1);
  REQUIRE(myRay.origin().y() == 2);
  REQUIRE(myRay.origin().z() == 3);

  REQUIRE(myRay.direction().x() == 4);
  REQUIRE(myRay.direction().y() == 5);
  REQUIRE(myRay.direction().z() == 6);
}

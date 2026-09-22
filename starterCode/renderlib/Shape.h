#pragma once
#include "ray.h"

class Shape
{
protected:
  virtual bool intersect(const ray &r) = 0;
};
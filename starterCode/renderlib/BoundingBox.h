#pragma once
#include "vec3.h"
#include "ray.h"

class BoundingBox{

public:
    BoundingBox() = default;
    BoundingBox(point3 llb, point3 urf);

    BoundingBox merge(const BoundingBox& box) const;
    bool hit(const ray&, double t0, double t1) const;

    point3 llb;
    point3 urf;
};
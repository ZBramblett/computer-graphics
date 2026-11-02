#pragma once
#include "vec3.h"
#include "ray.h"

class BoundingBox{

public:
    BoundingBox() = default;
    BoundingBox(point3 llb, point3 urf);
    void update(const point3 &p);
    bool hit(const ray& r, double ray_tmin, double ray_tmax) const;

    point3 llb;
    point3 urf;
};
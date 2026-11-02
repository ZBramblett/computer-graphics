#include "BoundingBox.h"
#include <utility>

BoundingBox::BoundingBox(point3 llb, point3 urf) : llb(llb), urf(urf) {}

void BoundingBox::update(const point3 &p){
    for (int axis = 0; axis < 3; ++axis){
        if (p[axis] < llb[axis]){
            llb[axis] = p[axis];
        }
        if (p[axis] > urf[axis]) {
          urf[axis] = p[axis];
        }
    }
}


bool BoundingBox::hit(const ray & r, double ray_tmin, double ray_tmax) const {
    for (int axis = 0; axis < 3; ++axis){
        double tmin = (llb[axis] - r.origin()[axis]) / r.direction()[axis];
        double tmax = (urf[axis] - r.origin()[axis]) / r.direction()[axis];
        if (r.direction()[axis] < 0) {
            std::swap(tmin, tmax);
        }
        if (tmin > ray_tmin){
            ray_tmin = tmin;
        }
        if (tmax < ray_tmax){
            ray_tmax = tmax;
        }
        if (ray_tmin > ray_tmax){
            return false;
        }
    }
    return true;
}
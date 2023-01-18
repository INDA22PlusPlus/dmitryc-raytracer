#ifndef DMITRYC_RAYTRACER_RAY_H
#define DMITRYC_RAYTRACER_RAY_H


#include "vec.h"

// Todo: consider introducing variable as constants (need to decide whether rays should be mutable or not)
class Ray {
public:
    Point origin;
    Vec direction;

    Ray() = default;

    Ray(Point origin, Vec direction) {
        this->origin = origin;
        this->direction = direction.get_normalized();
    };

    Point end_at() {
        return origin + direction;
    }

    Point end_at_mult_const(double t) {
        return origin + direction * t;
    }
};

#endif //DMITRYC_RAYTRACER_RAY_H

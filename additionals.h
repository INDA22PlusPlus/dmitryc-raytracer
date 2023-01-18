// Useful additional stuff like constants and common functions, inspired by the guide

#ifndef DMITRYC_RAYTRACER_ADDITIONALS_H
#define DMITRYC_RAYTRACER_ADDITIONALS_H

#include <limits>

// Using

using namespace std;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double radians_to_degrees(double radians) {
    return radians * 180.0 / pi;
}

// Common headers,
#include "ray.h"
#include "vec.h"

#endif //DMITRYC_RAYTRACER_ADDITIONALS_H

// Useful additional stuff like constants and common functions, inspired by the guide

#ifndef DMITRYC_RAYTRACER_ADDITIONALS_H
#define DMITRYC_RAYTRACER_ADDITIONALS_H

#include <limits>

// Using
using namespace std;

// Constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

// Functions
inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}

inline float radians_to_degrees(float radians) {
    return radians * 180.0 / pi;
}

inline float random_float() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_float();
}

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common headers,
//#include "ray.h"
//#include "vec.h"

#endif //DMITRYC_RAYTRACER_ADDITIONALS_H

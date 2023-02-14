// Todo: split into cpp and h files

#ifndef DMITRYC_RAYTRACER_VecOptimized_H
#define DMITRYC_RAYTRACER_VecOptimized_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "additionals.h"
#include <immintrin.h>
//#include <avxintrin.h>

using namespace std;

// Todo: wtf? just find a better fix
class VecOptimized;
inline float dot(const VecOptimized &u, const VecOptimized &v);
inline std::ostream& operator<<(std::ostream &out, const VecOptimized &v);
inline VecOptimized operator+(const VecOptimized &u, const VecOptimized &v);
inline VecOptimized operator-(const VecOptimized &u, const VecOptimized &v);
inline VecOptimized operator*(const VecOptimized &u, const VecOptimized &v);
inline VecOptimized operator*(float t, const VecOptimized &v);
inline VecOptimized operator*(const VecOptimized &v, float t);
inline VecOptimized operator/(VecOptimized v, float t);
inline float dot(const VecOptimized &u, const VecOptimized &v);
inline VecOptimized cross(const VecOptimized &u, const VecOptimized &v);


class VecOptimized {
public:
    // Variables
    float x, y, z;

    // Todo: Doesn't work
//    float& r = x;
//    float& g = y;
//    float& b = z;

    // Constructors
    VecOptimized() {
        x = y = z = 0;
    }

    VecOptimized(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Todo: Not needed?
//    VecOptimized(int x, int y, int z) {
//        this->x = x;
//        this->y = y;
//        this->z = z;
//    }

    explicit VecOptimized(const float arr[3]) {
        x = arr[0];
        y = arr[1];
        z = arr[2];
    }

    // Overloading operators
    // Todo: TESTS

    // Array like accessing of x, y and z
    // Todo: Better? (most likely fixed by referencing the array the right way)
    float operator[](int i) const {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw std::invalid_argument("0, 1 and 2 correspond to x, y and z values respectively");
        }
    }

    // Todo: Find a way to use the other function instead of repeating code?
    float& operator[](int i) {
//        return operator[](i);
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw std::invalid_argument("0, 1 and 2 correspond to x, y and z values respectively");
        }
    }

    // Arithmetic overloading
    // Todo: Bracket assignment right?
    VecOptimized operator-() const {
        return {-x, -y, -z};
    }

    // Todo: Needed?
//    VecOptimized operator+() const {
//        return {x, y, z};
//    }
//
//    VecOptimized operator*() const {
//        return {x, y, z};
//    }


    // Assigment overloading
    VecOptimized& operator+=(const VecOptimized &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    VecOptimized& operator-=(const VecOptimized &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    VecOptimized& operator*=(const float t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    VecOptimized& operator/=(const float t) {
        return *this *= 1/t;
    }

    // Todo:  References do not work at the moment, prob fix later
//    float * get_arr() {
//        static float arr[] = {x, y, z};
//        return arr;
//    }

    inline void norm() {
        *this /= get_norm();
    }

    inline float get_norm() const {
        return sqrt(get_norm_squared());
    }

    inline float get_norm_squared() const {
        return x * x + y * y + z * z;
    }

    // Todo: Better way to do this?
    inline VecOptimized get_normalized() const {
        VecOptimized copy = VecOptimized(x, y, z);
        copy.norm();
        return copy;
    }

    void print_cout() {
        cout << x << " " << y << " " << z << endl;
    }

    // Random functions taken from the guide
    inline static VecOptimized random() {
        return VecOptimized(random_float(), random_float(), random_float());
    }

    inline static VecOptimized random(float min, float max) {
        return VecOptimized(random_float(min,max), random_float(min,max), random_float(min,max));
    }

    // Todo: Better implementation please
    static VecOptimized random_in_unit_sphere() {
        while (true) {
            VecOptimized p = random(-1,1);
            if (p.get_norm_squared() >= 1) continue;
            return p;
        }
    }

    static VecOptimized random_unit_sphere() {
        return random_in_unit_sphere().get_normalized();
    }

    static VecOptimized random_in_hemisphere(const VecOptimized& normal) {
        VecOptimized in_unit_sphere = random_in_unit_sphere();
        if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }

    // Return true if the VecOptimizedtor is close to zero in all dimensions.
    bool near_zero() const {
        return (fabs(x) < near_zero_constant) &&
               (fabs(y) < near_zero_constant) &&
               (fabs(z) < near_zero_constant);
    }

    // Reflects about normal using reflection formula
    static VecOptimized reflect(const VecOptimized& v, const VecOptimized normal) {
        return v - 2 * dot(v,normal) * normal;
    }
};

using PointOptimized = VecOptimized;   // 3D point
using ColorOptimized = VecOptimized;
using PixelOptimized = VecOptimized;

// VecOptimized functions

// Todo: use friend?
inline std::ostream& operator<<(std::ostream &out, const VecOptimized &v) {
    return out << v.x << " " << v.y << " " << v.z << endl;
}

// Todo: Bracket assignment right?
inline VecOptimized operator+(const VecOptimized &u, const VecOptimized &v) {
//    __m256 r = _mm256_loadu2_m128(&u.x, &v.x);

    return {u.x + v.x, u.y + v.y, u.z + v.z};
}

// Todo: Bracket assignment right?
inline VecOptimized operator-(const VecOptimized &u, const VecOptimized &v) {
    return {u.x - v.x, u.y - v.y, u.z - v.z};
}

// Todo: Bracket assignment right?
inline VecOptimized operator*(const VecOptimized &u, const VecOptimized &v) {
    return {u.x * v.x, u.y * v.y, u.z * v.z};
}

// Todo: Bracket assignment right?
inline VecOptimized operator*(float t, const VecOptimized &v) {
    return {t * v.x, t * v.y, t * v.z};
}

inline VecOptimized operator*(const VecOptimized &v, float t) {
    return t * v;
}

inline VecOptimized operator/(VecOptimized v, float t) {
    return (1 / t) * v;
}

inline float dot(const VecOptimized &u, const VecOptimized &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline VecOptimized cross(const VecOptimized &u, const VecOptimized &v) {
    return {u.y * v.z - u.z * v.y,
            - (u.x * v.z - u.z * v.x),
            u.x * v.y - u.y * v.x};
}

// Todo: Fix
//class VecOptimizedColor: public VecOptimized {
//    float &r = x;
//    float &g = y;
//    float &b = z;
//};

#endif //DMITRYC_RAYTRACER_VecOptimized_H

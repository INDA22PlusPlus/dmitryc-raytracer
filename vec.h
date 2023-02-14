// Todo: split into cpp and h files

#ifndef DMITRYC_RAYTRACER_VEC_H
#define DMITRYC_RAYTRACER_VEC_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "additionals.h"

using namespace std;

constexpr static const float near_zero_constant = 1e-9;


// Todo: wtf? just find a better fix
class Vec;
inline float dot(const Vec &u, const Vec &v);
inline std::ostream& operator<<(std::ostream &out, const Vec &v);
inline Vec operator+(const Vec &u, const Vec &v);
inline Vec operator-(const Vec &u, const Vec &v);
inline Vec operator*(const Vec &u, const Vec &v);
inline Vec operator*(float t, const Vec &v);
inline Vec operator*(const Vec &v, float t);
inline Vec operator/(Vec v, float t);
inline float dot(const Vec &u, const Vec &v);
inline Vec cross(const Vec &u, const Vec &v);


class Vec {
public:
    // Variables
    float x, y, z;

    // Todo: Doesn't work
//    float& r = x;
//    float& g = y;
//    float& b = z;

    // Constructors
    Vec() {
        x = y = z = 0;
    }

    Vec(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Todo: Not needed?
//    Vec(int x, int y, int z) {
//        this->x = x;
//        this->y = y;
//        this->z = z;
//    }

    explicit Vec(const float arr[3]) {
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
    Vec operator-() const {
        return {-x, -y, -z};
    }

    // Todo: Needed?
//    Vec operator+() const {
//        return {x, y, z};
//    }
//
//    Vec operator*() const {
//        return {x, y, z};
//    }


    // Assigment overloading
    Vec& operator+=(const Vec &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec& operator-=(const Vec &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vec& operator*=(const float t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec& operator/=(const float t) {
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
    inline Vec get_normalized() const {
        Vec copy = Vec(x, y, z);
        copy.norm();
        return copy;
    }

    void print_cout() {
        cout << x << " " << y << " " << z << endl;
    }

    // Random functions taken from the guide
    inline static Vec random() {
        return Vec(random_float(), random_float(), random_float());
    }

    inline static Vec random(float min, float max) {
        return Vec(random_float(min,max), random_float(min,max), random_float(min,max));
    }

    // Todo: Better implementation please
    static Vec random_in_unit_sphere() {
        while (true) {
            Vec p = random(-1,1);
            if (p.get_norm_squared() >= 1) continue;
            return p;
        }
    }

    static Vec random_unit_sphere() {
        return random_in_unit_sphere().get_normalized();
    }

    static Vec random_in_hemisphere(const Vec& normal) {
        Vec in_unit_sphere = random_in_unit_sphere();
        if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }

    // Return true if the vector is close to zero in all dimensions.
    bool near_zero() const {
        return (fabs(x) < near_zero_constant) &&
               (fabs(y) < near_zero_constant) &&
               (fabs(z) < near_zero_constant);
    }

    // Reflects about normal using reflection formula
    static Vec reflect(const Vec& v, const Vec normal) {
        return v - 2 * dot(v,normal) * normal;
    }
};

using Point = Vec;   // 3D point
using Color = Vec;
using Pixel = Vec;

// Vec functions

// Todo: use friend?
inline std::ostream& operator<<(std::ostream &out, const Vec &v) {
    return out << v.x << " " << v.y << " " << v.z << endl;
}

// Todo: Bracket assignment right?
inline Vec operator+(const Vec &u, const Vec &v) {
    return {u.x + v.x, u.y + v.y, u.z + v.z};
}

// Todo: Bracket assignment right?
inline Vec operator-(const Vec &u, const Vec &v) {
    return {u.x - v.x, u.y - v.y, u.z - v.z};
}

// Todo: Bracket assignment right?
inline Vec operator*(const Vec &u, const Vec &v) {
    return {u.x * v.x, u.y * v.y, u.z * v.z};
}

// Todo: Bracket assignment right?
inline Vec operator*(float t, const Vec &v) {
    return {t * v.x, t * v.y, t * v.z};
}

inline Vec operator*(const Vec &v, float t) {
    return t * v;
}

inline Vec operator/(Vec v, float t) {
    return (1 / t) * v;
}

inline float dot(const Vec &u, const Vec &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline Vec cross(const Vec &u, const Vec &v) {
    return {u.y * v.z - u.z * v.y,
            - (u.x * v.z - u.z * v.x),
            u.x * v.y - u.y * v.x};
}

// Todo: Fix
//class VecColor: public Vec {
//    float &r = x;
//    float &g = y;
//    float &b = z;
//};

#endif //DMITRYC_RAYTRACER_VEC_H

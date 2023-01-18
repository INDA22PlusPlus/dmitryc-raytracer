// Todo: split into cpp and h files

#ifndef DMITRYC_RAYTRACER_VEC_H
#define DMITRYC_RAYTRACER_VEC_H

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Vec {
public:
    // Variables
    double x, y, z;

    // Todo: Doesn't work
//    double& r = x;
//    double& g = y;
//    double& b = z;

    // Constructors
    Vec() {
        x = y = z = 0;
    }

    Vec(double x, double y, double z) {
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

    explicit Vec(const double arr[3]) {
        x = arr[0];
        y = arr[1];
        z = arr[2];
    }

    // Overloading operators
    // Todo: TESTS

    // Array like accessing of x, y and z
    // Todo: Better? (most likely fixed by referencing the array the right way)
    double operator[](int i) const {
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
    double& operator[](int i) {
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

    Vec& operator*=(const double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec& operator/=(const double t) {
        return *this *= 1/t;
    }

    // Todo:  References do not work at the moment, prob fix later
//    double * get_arr() {
//        static double arr[] = {x, y, z};
//        return arr;
//    }

    void norm() {
        *this /= get_norm();
    }

    double get_norm() {
        return sqrt(x * x + y * y + z * z);
    }

    // Todo: Better way to do this?
    Vec get_normalized() {
        Vec copy = Vec(x, y, z);
        copy.norm();
        return copy;
    }

    void print_cout() {
        cout << x << " " << y << " " << z << endl;
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
inline Vec operator*(double t, const Vec &v) {
    return {t*v.x, t*v.y, t*v.z};
}

inline Vec operator*(const Vec &v, double t) {
    return t * v;
}

inline Vec operator/(Vec v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec &u, const Vec &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline Vec cross(const Vec &u, const Vec &v) {
    return {u.y * v.z - u.z * v.y,
            - (u.x * v.z - u.z * v.x),
            u.x * v.y - u.y * v.x};
}

// Todo: Fix
//class VecColor: public Vec {
//    double &r = x;
//    double &g = y;
//    double &b = z;
//};

#endif //DMITRYC_RAYTRACER_VEC_H

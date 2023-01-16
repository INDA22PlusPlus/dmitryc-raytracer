// Todo: split into cpp and h files

#ifndef DMITRYC_RAYTRACER_VEC_OLD_H
#define DMITRYC_RAYTRACER_VEC_OLD_H

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
    Vec();

    Vec(double x, double y, double z);

    // Todo: Not needed?
//    Vec(int x, int y, int z) {
//        this->x = x;
//        this->y = y;
//        this->z = z;
//    }

    // Todo: Why const and explicit tho?
    explicit Vec(const double arr[3]);

    // Overloading operators
    // Todo: TESTS

    // Array like accessing of x, y and z
    // Todo: Better? (most likely fixed by referencing the array the right way)
    double operator[](int i) const;

    // Todo: Find a way to use the other function instead of repeating code?
    double& operator[](int i);

    // Arithmetic overloading
    // Todo: Bracket assignment right?
    Vec operator-() const;

    // Todo: Needed?
//    Vec operator+() const {
//        return {x, y, z};
//    }
//
//    Vec operator*() const {
//        return {x, y, z};
//    }


    // Assigment overloading
    Vec& operator+=(const Vec &v);

    Vec& operator-=(const Vec &v);

    Vec& operator*=(const double t);

    Vec& operator/=(const double t);

    // Todo:  References do not work at the moment, prob fix later
//    double * get_arr() {
//        static double arr[] = {x, y, z};
//        return arr;
//    }

    void norm();

    double get_norm();

    void print_cout();
};

using Point = Vec;   // 3D point
using Color = Vec;

// Todo: move to separate file?
// Vec functions

// Todo: use friend?
inline std::ostream& operator<<(std::ostream &out, const Vec &v);

// Todo: Bracket assignment right?
inline Vec operator+(const Vec &u, const Vec &v);

// Todo: Bracket assignment right?
inline Vec operator-(const Vec &u, const Vec &v);

// Todo: Bracket assignment right?
inline Vec operator*(const Vec &u, const Vec &v);

// Todo: Bracket assignment right?
inline Vec operator*(double t, const Vec &v);

inline Vec operator*(const Vec &v, double t);

inline Vec operator/(Vec v, double t);

inline double dot(const Vec &u, const Vec &v);

inline Vec cross(const Vec &u, const Vec &v);

// Todo: Fix
//class VecColor: public Vec {
//    double &r = x;
//    double &g = y;
//    double &b = z;
//};

#endif //DMITRYC_RAYTRACER_VEC_OLD_H

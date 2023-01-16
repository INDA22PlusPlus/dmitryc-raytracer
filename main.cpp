#include <iostream>
#include <fstream>
#include <Magick++.h>
#include <cmath>
using namespace std;
//using namespace Magick;


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

    // Todo: Why const and explicit tho?
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

    void print_cout() {
        cout << x << " " << y << " " << z << endl;
    }
};

using Point = Vec;   // 3D point
using Color = Vec;

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


void create_image(int height, int weight, int max_color_depth) {
    ofstream img("img.ppm");

    img << "P3" << endl;
    img << height << " " << weight << endl;
    img << max_color_depth << endl;

    Vec buf[height][weight];

    for (int y = 0; y < height; y++) {
//        cout << "Line: " << y + 1 << "/" << height << endl;
        for (int x = 0; x < weight; x++) {
            Color color(x, y, abs(x - y));
//            Color color(200, 0, 0);
            img << color;
        }
    }

    img.close();
}


int main(int argc,char **argv) {
    // Todo: Convert images using library instead of third party tools
//    InitializeMagick(*argv);

//    Vec test = Vec(1, 1, 1) + Vec(0, 1, 2) / 4;
////    test += Vec(0, 1, 2);
////    test -= Vec(0, 0, 1);
////    test *= 3;
////    test /= 3;
////    test.norm();
//    cout << test;

    int h = 255;
    int w = 255;
    int max_color_depth = 255;

    create_image(h, w, max_color_depth);

//    Image ppm_file;
//    ppm_file.read("img.ppm");
//    ppm_file.write("img.png");

    return 0;
}

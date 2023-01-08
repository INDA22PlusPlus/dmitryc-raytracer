#include <iostream>
#include <fstream>
#include <Magick++.h>
#include <cmath>
using namespace std;
using namespace Magick;


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
};

// Todo: Fix
//class VecColor: public Vec {
//    double &r = x;
//    double &g = y;
//    double &b = z;
//};


int main(int argc,char **argv) {
    // Todo: Convert images using library instead of third party tools
//    InitializeMagick(*argv);

    Vec test = Vec(1, 1, 1);
    test += Vec(0, 1, 2);
    test -= Vec(0, 0, 1);
//    test *= 3;
//    test /= 3;
//    test.norm();
    cout << test.x << " " << test.y << " " << test.z << " " << endl;

//    int h = 255;
//    int w = 255;
//    int max_color_depth = 255;
//
//    ofstream img("img.ppm");
//
//
//    img << "P3" << endl;
//    img << h << " " << w << endl;
//    img << max_color_depth << endl;
//
//    Vec buf[h][w];
//
//    for (int y = 0; y < h; y++) {
////        cout << "Line: " << y + 1 << "/" << h << endl;
//        for (int x = 0; x < w; x++) {
//            Vec &color = buf[x][y];
////            color = Vec(y, abs(y - x), x);
////            color[0] = y;
////            color[1] = x;
////            color[2] = abs(y - x);
//            color.x = x;
//            color.y = y;
//            color.z = abs(y - x);
//            img << color.x << " " << color.y << " " << color.z << endl;
//        }
//    }
//
//    img.close();

//    Image ppm_file;
//    ppm_file.read("img.ppm");
//    ppm_file.write("img.png");

    return 0;
}

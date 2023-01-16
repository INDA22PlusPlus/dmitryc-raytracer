#include "vec.h"

Vec::Vec() {
    x = y = z = 0;
}

Vec::Vec(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec::Vec(const double *arr) {
    x = arr[0];
    y = arr[1];
    z = arr[2];
}

double Vec::operator[](int i) const {
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

double &Vec::operator[](int i) {
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

Vec Vec::operator-() const {
    return {-x, -y, -z};
}

Vec &Vec::operator+=(const Vec &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec &Vec::operator-=(const Vec &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec &Vec::operator*=(const double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vec &Vec::operator/=(const double t) {
    return *this *= 1/t;
}

void Vec::norm() {
    *this /= get_norm();
}

double Vec::get_norm() {
    return sqrt(x * x + y * y + z * z);
}

void Vec::print_cout() {
    cout << x << " " << y << " " << z << endl;
}

std::ostream &operator<<(ostream &out, const Vec &v) {
    return out << v.x << " " << v.y << " " << v.z << endl;
}

Vec operator+(const Vec &u, const Vec &v) {
    return {u.x + v.x, u.y + v.y, u.z + v.z};
}

Vec operator-(const Vec &u, const Vec &v) {
    return {u.x - v.x, u.y - v.y, u.z - v.z};
}

Vec operator*(const Vec &u, const Vec &v) {
    return {u.x * v.x, u.y * v.y, u.z * v.z};
}

Vec operator*(double t, const Vec &v) {
    return {t*v.x, t*v.y, t*v.z};
}

Vec operator*(const Vec &v, double t) {
    return t * v;
}

Vec operator/(Vec v, double t) {
    return (1/t) * v;
}

double dot(const Vec &u, const Vec &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vec cross(const Vec &u, const Vec &v) {
    return {u.y * v.z - u.z * v.y,
            - (u.x * v.z - u.z * v.x),
            u.x * v.y - u.y * v.x};
}

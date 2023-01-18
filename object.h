
#ifndef DMITRYC_RAYTRACER_OBJECT_H
#define DMITRYC_RAYTRACER_OBJECT_H

#include "vec.h"
#include "ray.h"

class HitData {
public:
    Point point;
    Vec normal;
    double t;

    void update_data(double new_t, Ray ray, Point center, double radius) {
        t = new_t;
        point = ray.end_at_mult_const(t);
        normal = (point - center) / radius;
    }
};

class Object {
public:
    double t_min, t_max;

    virtual bool hit(Ray& ray, HitData hit_data) {

    }
};

class Sphere: public Object {
public:
    Point center;
    double radius;

    Sphere(Point center, double radius) {
        this->center = center;
        this->radius = radius;
    }

    bool hit(Ray& ray, HitData& hit_data) {
        Vec v = ray.origin - center;
        double a = ray.direction.get_norm_squared();
        // Optimized version with b = 2h, so that the 2 can be factored out and simplified
        double half_b = dot(v, ray.direction);
        double c = v.get_norm_squared() - radius * radius;
        double discriminant = half_b * half_b - a * c;

        // Early check if the sphere was hit
        if (discriminant < 0) {
            return false;
        }

        // Todo: rewrite cleaner
        // Checking the roots
        double sqrt_result = sqrt(discriminant);
        double root = (-half_b - sqrt_result) / a;
        // Checking for the opposite condition to exit
        if (root < t_min or root > t_max) {
            // Reassigning the same variable with the second root, used later
            root = (-half_b + sqrt_result) / a;
            if (root < t_min or root > t_max) {
                return false;
            }
        }

        hit_data.update_data(root, ray, center, radius);

        return true;
    }
};

#endif //DMITRYC_RAYTRACER_OBJECT_H


#ifndef DMITRYC_RAYTRACER_OBJECT_H
#define DMITRYC_RAYTRACER_OBJECT_H

#include "vec.h"
#include "ray.h"


class HitData;

class Material {
public:
    virtual bool scatter(const Ray& r_in, const HitData& rec, Color& attenuation, Ray& scattered) const = 0;
};

class HitData {
public:
    Point point;
    Vec normal;
    double t = 0;
    bool front_face = true;
    shared_ptr<Material> mat_ptr;

    HitData() = default;

    HitData(Point point, Vec normal, double t, bool front_face) {
        this->point = point;
        this->normal = normal;
        this->t = t;
        this->front_face = front_face;
    }

    void update_data(double new_t, Ray ray, Point center, double radius) {
        t = new_t;
        point = ray.end_at_mult_const(t);
        Vec out_normal = (point - center) / radius;
        set_face_and_normal(ray, out_normal);
    }

    void set_face_and_normal(Ray& ray, Vec& out_normal) {
        // Flipping the face depending on the dot product
        front_face = dot(ray.direction, out_normal) < 0;
        // Changes the normal accordingly
        normal = front_face ? out_normal : -out_normal;
    }
};

class Object {
public:
    double t_min = 0;
    double t_max = 0;

    Object() = default;

    Object(double t_min, double t_max) {
        this->t_min = t_min;
        this->t_max = t_max;
    }

    virtual bool hit(Ray& ray, HitData& hit_data) {
        return false;
    }
};

class Sphere: public Object {
public:
    Point center;
    double radius;
    shared_ptr<Material> material;

    Sphere(Point center, double radius, shared_ptr<Material> material, double t_min, double t_max) : Object(t_min, t_max) {
        this->center = center;
        this->radius = radius;
        this->material = material;
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

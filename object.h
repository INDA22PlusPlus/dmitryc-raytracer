
#ifndef DMITRYC_RAYTRACER_OBJECT_H
#define DMITRYC_RAYTRACER_OBJECT_H

#include <utility>

#include "vec.h"
#include "ray.h"

class Material;

class HitData {
public:
    Point point;
    Vec normal;
    double t = 0;
    bool front_face = true;
    shared_ptr<Material> material_ptr;

    HitData() = default;

    HitData(Point point, Vec normal, double t, bool front_face) {
        this->point = point;
        this->normal = normal;
        this->t = t;
        this->front_face = front_face;
    }

    void update_data(double new_t, Ray ray, Point center, double radius, shared_ptr<Material> material_ptr) {
        t = new_t;
        point = ray.end_at_mult_const(t);
        Vec out_normal = (point - center) / radius;
        set_face_and_normal(ray, out_normal);
        this->material_ptr = std::move(material_ptr);
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
    shared_ptr<Material> material_ptr;

    Sphere(Point center, double radius, double t_min, double t_max, shared_ptr<Material> material_ptr) : Object(t_min, t_max) {
        this->center = center;
        this->radius = radius;
        this->material_ptr = material_ptr;
    }

    bool hit(Ray& ray, HitData& hit_data) override {
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

        hit_data.update_data(root, ray, center, radius, material_ptr);

        return true;
    }
};

// Todo: mve outside, separate, causes too many errors for now
class Material {
public:
    virtual bool scatter(const Ray& ray_in, const HitData& hit_data, Color& color_reduction, Ray& scattered_ray) const {
        return false;
    };
};

// Lambertian lighting based materials
class Lambertian : public Material {
public:
    // <=> Albedo
    Color proportion_reflected;

    explicit Lambertian(const Color& proportion_reflected) {
        this->proportion_reflected = proportion_reflected;
    }

    bool scatter(const Ray& ray_in, const HitData& hit_data, Color& color_reduction, Ray& scattered_ray) const override {
        // Scatter slightly randomly
        Vec scatter_direction = hit_data.normal + Vec::random_unit_sphere();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero()) {
            scatter_direction = hit_data.normal;
        }

        scattered_ray = Ray(hit_data.point, scatter_direction);
        color_reduction = proportion_reflected;
        return true;
    }
};

class Metal : public Material {
public:
    Color proportion_reflected;

    explicit Metal(const Color& proportion_reflected) {
        this->proportion_reflected = proportion_reflected;
    }

    bool scatter(const Ray& ray_in, const HitData& hit_data, Color& color_reduction, Ray& scattered_ray) const override {
        // Reflects about normal
        Vec reflected_direction = Vec::reflect(ray_in.direction.get_normalized(), hit_data.normal);
        scattered_ray = Ray(hit_data.point, reflected_direction);
        color_reduction = proportion_reflected;
        // Check for right direction
        return (dot(scattered_ray.direction, hit_data.normal) > 0);
    }
};

#endif //DMITRYC_RAYTRACER_OBJECT_H

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
    float t = 0;
    bool front_face = true;
    shared_ptr<Material> material_ptr;

    HitData() = default;

    HitData(Point point, Vec normal, float t, bool front_face) {
        this->point = point;
        this->normal = normal;
        this->t = t;
        this->front_face = front_face;
    }

    void update_data_sphere(float new_t, Ray ray, Point center, float radius, shared_ptr<Material> material_ptr) {
        t = new_t;
        point = ray.end_at_mult_const(t);
        Vec out_normal = (point - center) / radius;
        set_face_and_normal(ray, out_normal);
        this->material_ptr = std::move(material_ptr);
    }

    void update_data_plane(float new_t, Ray ray, Vec new_normal, float distance_to_plane, shared_ptr<Material> material_ptr) {
        t = new_t;
        point = ray.end_at_mult_const(t);
        set_face_and_normal(ray, new_normal);
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
    float t_min = 0;
    float t_max = 0;

    Object() = default;

    Object(float t_min, float t_max) {
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
    float radius;
    shared_ptr<Material> material_ptr;

    Sphere(Point center, float radius, float t_min, float t_max, shared_ptr<Material> material_ptr) : Object(t_min, t_max) {
        this->center = center;
        this->radius = radius;
        this->material_ptr = material_ptr;
    }

    bool hit(Ray& ray, HitData& hit_data) override {
        Vec v = ray.origin - center;
        float a = ray.direction.get_norm_squared();
        // Optimized version with b = 2h, so that the 2 can be factored out and simplified
        float half_b = dot(v, ray.direction);
        float c = v.get_norm_squared() - radius * radius;
        float discriminant = half_b * half_b - a * c;

        // Early check if the sphere was hit
        if (discriminant < 0) {
            return false;
        }

        // Todo: rewrite cleaner
        // Checking the roots
        float sqrt_result = sqrt(discriminant);
        float root = (-half_b - sqrt_result) / a;
        // Checking for the opposite condition to exit
        if (root < t_min or root > t_max) {
            // Reassigning the same variable with the second root, used later
            root = (-half_b + sqrt_result) / a;
            if (root < t_min or root > t_max) {
                return false;
            }
        }

        hit_data.update_data_sphere(root, ray, center, radius, material_ptr);

        return true;
    }
};

class Plane: public Object {
public:
    Vec normal;
    float distance_to_plane;
    shared_ptr<Material> material_ptr;

    Plane(Vec normal, float distance_to_plane, float t_min, float t_max, shared_ptr<Material> material_ptr) : Object(t_min, t_max) {
        this->normal = normal;
        this->distance_to_plane = distance_to_plane;
        this->material_ptr = std::move(material_ptr);
    }

    bool hit(Ray& ray, HitData& hit_data) override {
        float denominator = dot(ray.direction, normal);
        float numerator = distance_to_plane - dot(ray.origin, normal);
        float t = numerator / denominator;
        if (t < 0) {
            return false;
        }

        hit_data.update_data_plane(t - 0.1, ray, normal.get_normalized(), distance_to_plane, material_ptr);

        return true;
    }
};


// Todo: mve outside, separate, causes too many errors for now
class Material {
public:
    virtual bool scatter(const Ray& ray_in, const HitData& hit_data, Color& color_reduction, Ray& scattered_ray) const {
        return false;
    };

    virtual Color emitted(const Point& point) const {
        return {0,0,0};
    }
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

class DiffuseLight: public Material  {
public:
    Color color = Color(1, 1, 1);

    DiffuseLight() = default;

    explicit DiffuseLight(Color color) {
        this->color = color;
    }

    bool scatter(const Ray& ray_in, const HitData& hit_data, Color& color_reduction, Ray& scattered_ray) const override {
        return false;
    };

    Color emitted(const Point& p) const override {
        return color;
    }
};

class Metal : public Material {
public:
    Color proportion_reflected;
    float  fuzziness;

    explicit Metal(const Color& proportion_reflected, float fuzziness) {
        this->proportion_reflected = proportion_reflected;
        this->fuzziness = fuzziness;
    }

    bool scatter(const Ray& ray_in, const HitData& hit_data, Color& color_reduction, Ray& scattered_ray) const override {
        // Reflects about normal
        Vec reflected_direction = Vec::reflect(ray_in.direction.get_normalized(), hit_data.normal);
        scattered_ray = Ray(hit_data.point, reflected_direction + fuzziness * Vec::random_in_unit_sphere());
        color_reduction = proportion_reflected;
        // Check for right direction
        return (dot(scattered_ray.direction, hit_data.normal) > 0);
    }
};

#endif //DMITRYC_RAYTRACER_OBJECT_H


#ifndef DMITRYC_RAYTRACER_SHADED_SPHERE_SCENE_H
#define DMITRYC_RAYTRACER_SHADED_SPHERE_SCENE_H


#include "ray-testing-scene.h"

class ShadedSphereScene: public RayTestingScene {
public:
    using RayTestingScene::RayTestingScene;

    virtual double hit_sphere_gradient(const Point& center, double radius, const Ray& ray) {
        // OC vector = v
        Vec v = ray.origin - center;
        auto a = dot(ray.direction, ray.direction);
        auto b = 2.0 * dot(v, ray.direction);
        auto c = dot(v, v) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        // No hit if Discriminant < 0 (returning negative values), else hit (returns some sort of gradient,
        // values taken from guide)
        if (discriminant < 0) {
            return -1.0;
        } else {

            return (-b - sqrt(discriminant) ) / (2.0*a);
        }
    }

    // Test to color the sphere with a gradient
    Pixel get_pixel_color_from_ray(Ray& ray) override {
        double t = hit_sphere_gradient(Point(0, 0, -1), 0.25, ray);
        if (t > 0.0) {
            // Normal to the sphere, used for the gradient
            Vec N = ray.end_at_mult_const(t) - Vec(0,0,-1);
            // Without norming the colors look bleak
            N.norm();
            // Messes up the picture witout this
            N += Vec(1, 1, 1);
            // Multiplying by this value corresponds to the brightness of the sphere
            N *= 0.5;
            return N;
        }
        t = 0.5 * (ray.direction.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
};

#endif //DMITRYC_RAYTRACER_SHADED_SPHERE_SCENE_H

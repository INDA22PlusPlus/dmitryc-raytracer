
#ifndef DMITRYC_RAYTRACER_FIRST_SPHERE_SCENE_H
#define DMITRYC_RAYTRACER_FIRST_SPHERE_SCENE_H

#include "ray-testing-scene.h"

class FirstSphereScene: public RayTestingScene {
public:
    using RayTestingScene::RayTestingScene;

    virtual bool hit_sphere(const Point& center, double radius, const Ray& ray) {
        // OC vector = v
        Vec v = ray.origin - center;
        auto a = dot(ray.direction, ray.direction);
        auto b = 2.0 * dot(v, ray.direction);
        auto c = dot(v, v) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        // No hit if Discriminant < 0, one hit if = 1 and 2 hits if > 0
        return (discriminant >= 0);
    }

    // Simple test with one red sphere
    Pixel get_pixel_color_from_ray(Ray& ray) override {
        if (hit_sphere(Point(0,0,-1), 0.25, ray)) {
            return {1, 0, 0};
        }
        // Blue to white background
        double t = 0.5 * (ray.direction.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
};

#endif //DMITRYC_RAYTRACER_FIRST_SPHERE_SCENE_H


#ifndef DMITRYC_RAYTRACER_SHADED_SPHERE_SCENE_H
#define DMITRYC_RAYTRACER_SHADED_SPHERE_SCENE_H


#include "ray-testing-scene.h"

class ShadedSphereScene: public RayTestingScene {
public:
    using RayTestingScene::RayTestingScene;

    virtual double hit_sphere_new(const Point& center, double radius, const Ray& ray) {
        Vec oc = ray.origin - center;
        auto a = dot(ray.direction, ray.direction);
        auto b = 2.0 * dot(oc, ray.direction);
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        if (discriminant < 0) {
            return -1.0;
        } else {
            return (-b - sqrt(discriminant) ) / (2.0*a);
        }
    }

    // Blue to white gradient based in y coordinate (up to down), values copied from guide
    Pixel get_pixel_color_from_ray(Ray& ray) override {
        double t = hit_sphere_new(Point(0,0,-1), 0.5, ray);
        if (t > 0.0) {
            Vec N = ray.end_at_mult_const(t) - Vec(0,0,-1);
            N.norm();
            return 0.5 * Color(N.x + 1, N.y + 1, N.z + 1);
        }
        t = 0.5 * (ray.direction.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
};

#endif //DMITRYC_RAYTRACER_SHADED_SPHERE_SCENE_H

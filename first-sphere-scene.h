
#ifndef DMITRYC_RAYTRACER_FIRST_SPHERE_SCENE_H
#define DMITRYC_RAYTRACER_FIRST_SPHERE_SCENE_H

#include "ray-testing-scene.h"

class FirstSphereScene: public RayTestingScene {
public:
    using RayTestingScene::RayTestingScene;

    virtual bool hit_sphere(const Point& center, double radius, const Ray& ray) {
        Vec oc = ray.origin - center;
        auto a = dot(ray.direction, ray.direction);
        auto b = 2.0 * dot(oc, ray.direction);
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        return (discriminant > 0);
    }

    // Blue to white gradient based in y coordinate (up to down), values copied from guide
    Color blue_to_white_gradient_in_y_coordinate(Ray& ray) override {
        if (hit_sphere(Point(0,0,-1), 0.5, ray)) {
            return {1, 0, 0};
        }
        double t = 0.5 * (ray.direction.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
};

#endif //DMITRYC_RAYTRACER_FIRST_SPHERE_SCENE_H

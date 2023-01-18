
#ifndef DMITRYC_RAYTRACER_RAY_TESTING_SCENE_H
#define DMITRYC_RAYTRACER_RAY_TESTING_SCENE_H

#include "scene.h"
#include "ray.h"

class RayTestingScene: public Scene {
public:
    using Scene::Scene;

    // Blue to white gradient based in y coordinate (up to down), values copied from guide
    Pixel get_pixel_color_from_ray(Ray& ray) override {
        double t = 0.5 * (ray.direction.y + 1.0);
        return (1.0 - t) * Pixel(1.0, 1.0, 1.0) + t * Pixel(0.5, 0.7, 1.0);
    }
};

#endif //DMITRYC_RAYTRACER_RAY_TESTING_SCENE_H

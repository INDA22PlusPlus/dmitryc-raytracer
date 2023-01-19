
#ifndef DMITRYC_RAYTRACER_SPHERE_AND_PLANE_SCENE_H
#define DMITRYC_RAYTRACER_SPHERE_AND_PLANE_SCENE_H

#include "first-sphere-scene.h"

class SphereAndPlaneScene: public FirstSphereScene{
public:
    using FirstSphereScene::FirstSphereScene;

    // Todo: Doing it with distance too
    virtual bool hit_plane(Vec normal, double distance_to_plane, Ray& ray) {
        double denominator = dot(ray.direction, normal);
        double numerator = distance_to_plane - dot(ray.origin, normal);
        double t = numerator / denominator;
        return (t >= 0);
    }

    // Simple test with one red sphere and green plane in spanning across Z and X axis
    Pixel get_pixel_color_from_ray(Ray& ray, int depth) override {
        if (hit_sphere(Point(0,0,-1), 0.25, ray)) {
            return {1, 0, 0};
        }
        // The order ensures that the sphere is on top of the plane
        if (hit_plane(Vec(0, 10, -1), -10, ray)) {
            return {0, 1, 0};
        }
        // Blue to white background
        double t = 0.5 * (ray.direction.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }

};

#endif //DMITRYC_RAYTRACER_SPHERE_AND_PLANE_SCENE_H


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

    void draw_ppm(ofstream& img) override {
        int hundredth_part = window_height / 100;
        for (int y = 0; y < window_height; y++) {
            if (y % hundredth_part == 0 and show_progress) {
                cout << y / hundredth_part << "%" << endl;
            }
            for (int x = 0; x < window_width; x++) {
                // UV interpretation of X (in our case corresponding to U) and Y (corresponding to V) axis
                // coordinates of a plane (using relative coordinates)
                double u = static_cast<double>(x) / (window_width - 1);
                double v = static_cast<double>(window_height - y) / (window_height - 1);
//                double v = static_cast<double>(y) / (window_height - 1);
                Ray ray(camera.origin,
                        camera.lower_left_corner + u * camera.horizontal + v * camera.vertical - camera.origin);
                Pixel pixel_color = get_pixel_color_from_ray(ray);
                img << get_converted_color(pixel_color);
            }
        }
    }
};

#endif //DMITRYC_RAYTRACER_RAY_TESTING_SCENE_H

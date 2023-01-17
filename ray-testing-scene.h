
#ifndef DMITRYC_RAYTRACER_RAY_TESTING_SCENE_H
#define DMITRYC_RAYTRACER_RAY_TESTING_SCENE_H

#include "scene.h"
#include "ray.h"

class RayTestingScene: public Scene {
public:
    using Scene::Scene;

     // Blue to white gradient based in y coordinate (up to down), values copied from guide
     virtual Color blue_to_white_gradient_in_y_coordinate(Ray& ray) {
        double t = 0.5 * (ray.direction.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }

    void create_ray_image() {
        // Camera setup
        Camera camera(aspect_ratio);

        // Render image
        ofstream img(default_img_path);

        img << "P3" << endl;
        img << window_width << " " << window_height << endl;
        img << max_color_depth << endl;

        // Todo: Move out to a desperate function, because top part is going to be reused, figure out if a buf array
        //       is needed for that
//        Vec buf[height][width];

        for (int y = 0; y < window_height; y++) {
            for (int x = 0; x < window_width; x++) {
                // UV interpretation of X (in our case corresponding to U) and Y (corresponding to V) axis
                // coordinates of a plane (using relative coordinates)
                double u = static_cast<double>(x) / (window_width - 1);
                double v = static_cast<double>(window_height - y) / (window_height - 1);
//                double v = static_cast<double>(y) / (window_height - 1);
                Ray ray(camera.origin,
                        camera.lower_left_corner + u * camera.horizontal + v * camera.vertical - camera.origin);
                Color pixel_color = blue_to_white_gradient_in_y_coordinate(ray);
                img << get_converted_color(pixel_color);
            }
        }

        img.close();
    }

    void render_to_ppm_img() override {
        create_ray_image();
    }
};

#endif //DMITRYC_RAYTRACER_RAY_TESTING_SCENE_H

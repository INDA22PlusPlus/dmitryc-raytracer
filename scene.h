#ifndef DMITRYC_RAYTRACER_SCENE_H
#define DMITRYC_RAYTRACER_SCENE_H

#include "camera.h"
#include "object-list.h"
#include "additionals.h"
#include "vec.h"

class Scene {
public:
    Camera camera;

    double aspect_ratio;
    int window_width;
    int window_height;
    int max_color_depth;

    int max_depth = 5;

    string default_img_path = "img.ppm";
    bool show_progress = false;

    ObjectList objects;

//    Pixel *frame_buf;

    Scene() {
        aspect_ratio = 16.0 / 9.0;
        window_width = 400;
        window_height = static_cast<int>(window_width / aspect_ratio);
        max_color_depth = 255;

//        frame_buf[window_height][window_width];
    }

    // Todo: fix code duplication with constructors
    // Todo: add default_img_path as a parameter to constructors

    // Manual height
    Scene(double aspect_ratio, int window_width, int window_height, int max_color_depth) {
        this->aspect_ratio = aspect_ratio;
        this->window_height = window_height;
        this->window_width = window_width;
        this->max_color_depth = max_color_depth;

//        frame_buf[window_height][window_width];
    }

    // Manual height, with camera
    Scene(double aspect_ratio, int window_width, int window_height, int max_color_depth, Camera camera) {
        this->aspect_ratio = aspect_ratio;
        this->window_height = window_height;
        this->window_width = window_width;
        this->max_color_depth = max_color_depth;

        this->camera = camera;
//        frame_buf[window_height][window_width];
    }

    // Automatically adjusted height
    Scene(double aspect_ratio, int window_width, int max_color_depth) {
        this->aspect_ratio = aspect_ratio;
        this->window_height = static_cast<int>(window_width / aspect_ratio);
        this->window_width = window_width;
        this->max_color_depth = max_color_depth;

//        frame_buf[window_height][window_width];
    }

    // Automatically adjusted height, with camera
    Scene(double aspect_ratio, int window_width, int max_color_depth, Camera camera) {
        this->aspect_ratio = aspect_ratio;
        this->window_height = static_cast<int>(window_width / aspect_ratio);
        this->window_width = window_width;
        this->max_color_depth = max_color_depth;

        this->camera = camera;
//        frame_buf[window_height][window_width];
    }

    // Casts rays, gets the color at which the ray ends after all manipulations. Default implementation if no ray
    // hits anything is interpreted as a background hit, which in this case is a gradient between blue and white.
    virtual Pixel get_pixel_color_from_ray(Ray& ray, int depth) {
        HitData hit_data;
        objects.t_max = infinity;

        if (depth <= 0) {
            return {0, 0, 0};
        }

        if (objects.hit(ray, hit_data)) {
            // Recursive calling of get_pixel to bounce multiple times
            Point target = hit_data.point + hit_data.normal + Vec::random_in_unit_sphere();
            Ray temp_ray(hit_data.point, target - hit_data.point);
            return 0.5 * get_pixel_color_from_ray(temp_ray, depth - 1);
        }
        // Blue to white background, if no objects hit
        double t = 0.5 * (ray.direction.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }

    // Todo: Better syntax?
    Pixel get_converted_color(Pixel pixel_color) {
        // Convert back the relative color values from a range of 0-1 to color depth
        return Pixel(static_cast<int>((max_color_depth + 0.999) * pixel_color.x),
                     static_cast<int>((max_color_depth + 0.999) * pixel_color.y),
                     static_cast<int>((max_color_depth + 0.999) * pixel_color.z));
    }



    // Todo: Make abstract
    void render() {
        // Code?
    }

    // Todo: Same as abstract?
    virtual void render_to_ppm_img() {
        // Render image
        ofstream img(default_img_path);

        img << "P3" << endl;
        img << window_width << " " << window_height << endl;
        img << max_color_depth << endl;

        // Todo: Move out to a desperate function, because top part is going to be reused, figure out if a buf array
        //       is needed for that. Required to go through the bitmap twice tho, may be too slow.

        draw_ppm(img);

        img.close();
    }

    void draw_ppm(ofstream& img) {
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
                Pixel pixel_color = get_pixel_color_from_ray(ray, max_depth);
                img << get_converted_color(pixel_color);
            }
        }
    }

    void add_object(const shared_ptr<Object>& object) {
        objects.add(object);
    }
};

#endif //DMITRYC_RAYTRACER_SCENE_H

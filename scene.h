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

    int max_depth = 10;
    int samples_per_pixel = 100;

    string default_img_path = "img2.ppm";
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

    // Light blue to white background
    static Color get_background_color(Ray ray) {
        double t = 0.5 * (ray.direction.y + 1.0);
//        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
        // Darker color
        return (1.0 - t) * Color(0.5, 0.5, 0.5) + t * Color(0.1, 0.3, 0.6);
//        return {0.5, 0.5, 0.5};
//        return {0.1, 0.1, 0.1};
//        return {0.01, 0.01, 0.01};
//        return {0, 0, 0};
    }

    // Casts rays, gets the color at which the ray ends after all manipulations. Default implementation if no ray
    // hits anything is interpreted as a background hit, which in this case is a gradient between blue and white.
    virtual Pixel get_pixel_color_from_ray(Ray& ray, int depth) {
        HitData hit_data;
        objects.t_max = infinity;

//        if (objects.hit(ray, hit_data)) {
//            return 0.5 * (hit_data.normal + Pixel(1,1,1));
//        }

        if (depth <= 0) {
            return {0, 0, 0};
        }

        // Blue to white background, if no objects hit, first because no hits could be encountered more often
        if (!objects.hit(ray, hit_data)) {
            return get_background_color(ray);
        }

        Ray scattered_ray;
        Color color_reduction;
        Color emitted_color = hit_data.material_ptr->emitted(hit_data.point);

        if (!hit_data.material_ptr->scatter(ray, hit_data, color_reduction, scattered_ray)) {
            return emitted_color;
        }

        return emitted_color + color_reduction * get_pixel_color_from_ray(scattered_ray, depth-1);

    }

    // Todo: Better syntax?
    Pixel get_converted_color(Pixel pixel_color) {
        auto r = pixel_color.x;
        auto g = pixel_color.y;
        auto b = pixel_color.z;

        // Divide the color by the number of samples.
        // TODO: change manual constant
        double scale = 1.0 / samples_per_pixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);
        // Convert back the relative color values from a range of 0-1 to color depth
        return Pixel(static_cast<int>(256 * clamp(r, 0.0, 0.999)),
                     static_cast<int>(256 * clamp(g, 0.0, 0.999)),
                     static_cast<int>(256 * clamp(b, 0.0, 0.999)));
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
                Pixel pixel_color(0, 0, 0);
                for (int i = 0; i < samples_per_pixel; i++) {
                    // UV interpretation of X (in our case corresponding to U) and Y (corresponding to V) axis
                    // coordinates of a plane (using relative coordinates)
                    double u = static_cast<double>(x + random_double()) / (window_width - 1);
                    double v = static_cast<double>(window_height - y + random_double()) / (window_height - 1);
//                double v = static_cast<double>(y) / (window_height - 1);
                    Ray ray(camera.origin,
                            camera.lower_left_corner + u * camera.horizontal + v * camera.vertical - camera.origin);
                    pixel_color += get_pixel_color_from_ray(ray, max_depth);
                }
                img << get_converted_color(pixel_color);
            }
        }
    }

    void add_object(const shared_ptr<Object>& object) {
        objects.add(object);
    }
};

#endif //DMITRYC_RAYTRACER_SCENE_H

#ifndef DMITRYC_RAYTRACER_SCENE_H
#define DMITRYC_RAYTRACER_SCENE_H

#include "camera.h"

class Scene {
public:
    Camera camera;

    double aspect_ratio;
    int window_width;
    int window_height;
    int max_color_depth;

    string default_img_path = "img.ppm";
    bool show_progress = false;

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

//    Pixel get_converted_color(Pixel) {
//        return Pixel();
//    }
    virtual Pixel get_pixel_color_from_ray(Ray& ray) {
        // Code?
    }

    // Todo: Better syntax?
    Pixel get_converted_color(Pixel pixel_color) {
        // Convert back the relative color values from a range of 0-1 to color depth
        return Color(static_cast<int>((max_color_depth + 0.999) * pixel_color.x),
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

    virtual void draw_ppm(ofstream& img) {
        // Code?
    }
};

#endif //DMITRYC_RAYTRACER_SCENE_H
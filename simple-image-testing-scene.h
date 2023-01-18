
#ifndef DMITRYC_RAYTRACER_SIMPLE_IMAGE_TESTING_SCENE_H
#define DMITRYC_RAYTRACER_SIMPLE_IMAGE_TESTING_SCENE_H

#include "scene.h"

class SimpleImageTestingScene: public Scene {
public:
    using Scene::Scene;

    void create_image() {
        ofstream img("img.ppm");

        img << "P3" << endl;
        img << window_width << " " << window_height << endl;
        img << max_color_depth << endl;

//    Vec buf[window_height][window_width];

//    for (int y = 0; y < window_height; y++) {
        for (int y = 0; y < window_height; y++) {
//        cout << "Line: " << y + 1 << "/" << window_height << endl;
            for (int x = 0; x < window_width; x++) {
                Color color(int(255.999 * (double(x) / (window_width - 1))), int(255.999 * (double(window_height - y) / (window_height - 1))), int(255.999 * 0.25));
//            Color color(x, y, abs(x - y));
//            Color color(200, 0, 0);
                img << color;
            }
        }

        img.close();
    }

    void render_to_ppm_img() override {
        create_image();
    }
};

#endif //DMITRYC_RAYTRACER_SIMPLE_IMAGE_TESTING_SCENE_H

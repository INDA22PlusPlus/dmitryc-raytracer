#include <iostream>
#include <fstream>
//#include <Magick++.h>
#include <cmath>
#include "vec.h"
#include "ray.h"
#include "camera.h"
#include "scene.h"
#include "ray-testing-scene.h"
#include "first-sphere-scene.h"

using namespace std;
//using namespace Magick;


void create_image(int height, int width, int max_color_depth) {
    ofstream img("img.ppm");

    img << "P3" << endl;
    img << height << " " << width << endl;
    img << max_color_depth << endl;

//    Vec buf[height][width];

//    for (int y = 0; y < height; y++) {
    for (int y = 0; y < height; y++) {
//        cout << "Line: " << y + 1 << "/" << height << endl;
        for (int x = 0; x < width; x++) {
            Color color(int(255.999 * (double(x) / (width - 1))), int(255.999 * (double(height - y) / (height - 1))), int(255.999 * 0.25));
//            Color color(x, y, abs(x - y));
//            Color color(200, 0, 0);
            img << color;
        }
    }

    img.close();
}

int main(int argc,char **argv) {
    // Todo: Convert images using library instead of third party tools

//    RayTestingScene scene(16.0 / 9.0, 400, 255);
    FirstSphereScene scene(16.0 / 9.0, 400, 255);
    scene.render_to_ppm_img();

    return 0;
}

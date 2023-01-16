#include <iostream>
#include <fstream>
#include <Magick++.h>
#include <cmath>
#include "vec.h"
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
//    InitializeMagick(*argv);

//    Vec test = Vec(1, 1, 1) + Vec(0, 1, 2) / 4;
////    test += Vec(0, 1, 2);
////    test -= Vec(0, 0, 1);
////    test *= 3;
////    test /= 3;
////    test.norm();
//    cout << test;

    int h = 1000;
    int w = 1000;
    int max_color_depth = 255;

    create_image(h, w, max_color_depth);

//    Image ppm_file;
//    ppm_file.read("img.ppm");
//    ppm_file.write("img.png");

    return 0;
}

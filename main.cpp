#include <iostream>
#include <fstream>
#include <Magick++.h>
#include <cmath>
#include "vec.h"
#include "ray.h"
#include "camera.h"

using namespace std;
//using namespace Magick;


Color get_converted_color(Color pixel_color) {
    // Write the translated [0,255] value of each color component.
    return Color(static_cast<int>(255.999 * pixel_color.x),
                 static_cast<int>(255.999 * pixel_color.y),
                 static_cast<int>(255.999 * pixel_color.z));
}

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

// Blue to white gradient based in y coordinate (up to down), values copied from guide
Color blue_to_white_gradient_in_y_coordinate(const Ray& ray) {
    double t = 0.5 * (ray.direction.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


void create_ray_image(int height, int width, int max_color_depth, double aspect_ratio) {
    // Camera setup

    Camera camera(aspect_ratio);

    // Render image
    ofstream img("img.ppm");

    img << "P3" << endl;
    img << width << " " << height << endl;
    img << max_color_depth << endl;

//    Vec buf[height][width];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // UV interpretation of X (in our case corresponding to U) and Y (corresponding to V) axis
            // coordinates of a plane (using relative coordinates)
            double u = double(x) / (width - 1);
            double v = double(height - y) / (height - 1);
//            auto v = double(y) / (height - 1);
            Ray ray(camera.origin,
                    camera.lower_left_corner + u * camera.horizontal + v * camera.vertical - camera.origin);
            Color pixel_color = blue_to_white_gradient_in_y_coordinate(ray);
            img << get_converted_color(pixel_color);
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

    // Settings

    const double aspect_ratio = 16.0 / 9.0;
    const int window_width = 200;
    const int window_height = static_cast<int>(window_width / aspect_ratio);
    const int max_color_depth = 255;

//    // Camera setup
//
//    auto viewport_height = 2.0;
//    auto viewport_width = aspect_ratio * viewport_height;
//    auto focal_length = 1.0;
//
//    auto origin = Point(0, 0, 0);
//    auto horizontal = Vec(viewport_width, 0, 0);
//    auto vertical = Vec(0, viewport_height, 0);
//    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec(0, 0, focal_length);

//    create_image(window_height, window_width, max_color_depth);

    create_ray_image(window_height, window_width, max_color_depth, aspect_ratio);

//    Vec v1 = Vec(1, 2, 2);
//    Ray ray(Point(0, 0, 0), v1);
//
//    v1.x -= 1;

//    Image ppm_file;
//    ppm_file.read("img.ppm");
//    ppm_file.write("img.png");

    return 0;
}

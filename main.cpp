#include <iostream>
#include <fstream>
#include <Magick++.h>
using namespace std;
using namespace Magick;


class Vec {
public:
    double x;
    double y;
    double z;

    Vec() {
        x = y = z = 0;
    }

    Vec(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

//    Vec(int x, int y, int z) {
//        this->x = x;
//        this->y = y;
//        this->z = z;
//    }

    // Why const point tho?
    Vec(const double arr[3]) {
        x = arr[0];
        y = arr[1];
        z = arr[2];
    }
};


int main(int argc,char **argv) {
//    InitializeMagick(*argv);

    int h = 255;
    int w = 255;
    int max_color_depth = 255;

    ofstream img("img.ppm");
    

    img << "P3" << endl;
    img << h << " " << w << endl;
    img << max_color_depth << endl;

    Vec buf[h][w];

//    for (auto row: buf){
//        for (auto )
//    }

    for (int y = 0; y < h; y++) {
//        cout << "Line: " << y + 1 << "/" << h << endl;
        for (int x = 0; x < w; x++) {
            Vec color = Vec(x, abs(x - y), y);
            img << color.x << " " << color.y << " " << color.z << endl;
        }
    }



    img.close();

//    Image ppm_file;
//    ppm_file.read("img.ppm");
//    ppm_file.write("img.png");

    return 0;
}

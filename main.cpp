#include <iostream>
#include <fstream>
#include <Magick++.h>
using namespace std;
using namespace Magick;

int main(int argc,char **argv) {
//    InitializeMagick(*argv);

    int h = 255;
    int w = 255;
    int max_color_depth = 255;

    ofstream img("img.ppm");
    

    img << "P3" << endl;
    img << h << " " << w << endl;
    img << max_color_depth << endl;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            img << x << " " << abs(x - y) << " " << y << endl;
        }
    }

    img.close();

//    Image ppm_file;
//    ppm_file.read("img.ppm");
//    ppm_file.write("img.png");

    return 0;
}

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
#include "shaded-sphere-scene.h"
#include "simple-image-testing-scene.h"
#include "sphere-and-plane-scene.h"
#include "additionals.h"

using namespace std;
//using namespace Magick;

// Todo: ANTIALIASING
int main(int argc,char **argv) {
    // Todo: Convert images using library instead of third party tools

    Scene scene(16.0 / 9.0, 400, 255);
    scene.add_object(make_shared<Sphere>(Point(0,0,-1), 0.25, 0, infinity));
    scene.add_object(make_shared<Sphere>(Point(0,-100.5,-1), 100, 0, infinity));

//    SimpleImageTestingScene scene(16.0 / 9.0, 400, 255);
//    RayTestingScene scene(16.0 / 9.0, 400, 255);
//    FirstSphereScene scene(16.0 / 9.0, 400, 255);
//    ShadedSphereScene scene(16.0 / 9.0, 400, 255);
//    SphereAndPlaneScene scene(16.0 / 9.0, 400, 255);
//    scene.show_progress = true;
    scene.render_to_ppm_img();

    return 0;
}

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
#include "performance-testing.h"

using namespace std;
//using namespace Magick;

int main(int argc,char **argv) {

    PerformanceTesting pf;
//    pf.benchmark_scene_multiple_times(10, "render width=200 convert doubles to floats", true);
    pf.benchmark_vec_multiple_times(1000000, "vec add expression before improvement float", true);

    return 0;
}

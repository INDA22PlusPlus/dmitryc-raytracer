#ifndef DMITRYC_RAYTRACER_PERFORMANCE_TESTING_H
#define DMITRYC_RAYTRACER_PERFORMANCE_TESTING_H

#include "vec.h"
#include "vec-optimized.h"
#include "scene.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <utility>
#include <numeric>
using namespace std::chrono;


class PerformanceTesting {
public:
    string benchmarks_path = "/Users/dima/CLionProjects/dmitryc-raytracer/benchmarks";
    string scene_benchmark_path = benchmarks_path + "/scene.txt";
    string vec_benchmark_path = benchmarks_path + "/vec.txt";
    Scene scene;

    PerformanceTesting() {
        create_scene();
    }

    void create_scene() {
        // Todo: Convert images using library instead of third party tools

        scene = Scene(16.0 / 9.0, 200, 255);
        scene.add_object(make_shared<Plane>(Vec(0, 1, 0), -1, 0.001, infinity,
                                            make_shared<Lambertian>(Color(0.5, 0.5, 0))));
//    scene.add_object(make_shared<Sphere>(Point(0, -100.5, -1), 100, 0.001, infinity,
//                                        make_shared<Lambertian>(Color(0, 1, 0))));

        scene.add_object(make_shared<Sphere>(Point(0,0,-1), 0.5,0.001, infinity,
                                             make_shared<Lambertian>(Color(1, 0, 0))));
        scene.add_object(make_shared<Sphere>(Point(-0.75,-0.25,-1), 0.25, 0.001, infinity,
                                             make_shared<Metal>(Color(0.2, 0.2, 0.5), 0.7)));
        scene.add_object(make_shared<Sphere>(Point(-2,0.85,-3), 1, 0.001, infinity,
                                             make_shared<Metal>(Color(0.8, 0.8, 0.8), 0)));
        scene.add_object(make_shared<Sphere>(Point(-0.4,-0.4,-0.85), 0.1, 0.001, infinity,
                                             make_shared<Metal>(Color(0.4, 1, 0.4), 0.2)));
//    scene.add_object(make_shared<Sphere>(Point(-1.5,3,-0.5), 0.25, 0.001, infinity,
//                                         make_shared<DiffuseLight>(Color(100, 100, 100))));

//    SimpleImageTestingScene scene(16.0 / 9.0, 400, 255);
//    RayTestingScene scene(16.0 / 9.0, 400, 255);
//    FirstSphereScene scene(16.0 / 9.0, 400, 255);
//    ShadedSphereScene scene(16.0 / 9.0, 400, 255);
//    SphereAndPlaneScene scene(16.0 / 9.0, 400, 255);
//        scene.show_progress = true;
        scene.use_simd = true;
//        scene.render_to_ppm_img();
    }

    void render_scene() {
        scene.render_to_ppm_img();
    }

    void append_to_file(string &path, string &msg, vector<long> &data, bool add_data=true) {
        ofstream file;
        // Use append instead of override
        file.open(path, std::ios_base::app);

        long avg = average(vector<float>(data.begin(), data.end()));

        string data_string = "[";
        for (const auto &item: data) {
            data_string += std::to_string(item) + ",";
        }
        data_string += "]";

        file << msg << " : " << avg;
        if (add_data) {
            file << " ; " << data_string;
        }
        file << endl;
    }

    // Reduce based average of a vector, inspired by other solutions
    long average(vector<float> const& vec){
        // Return 0 if empty
        if(vec.empty()){
            return 0;
        }

        // Get size and calculate average
        auto const size = static_cast<float>(vec.size());
        return static_cast<long>(reduce(vec.begin(), vec.end()) / size);
    }

    long benchmark_scene() {
        // Avoiding benchmarking init, no difference
        create_scene();

        auto start = high_resolution_clock::now();
        render_scene();
        auto stop = high_resolution_clock::now();
        auto total = duration_cast<microseconds>(stop - start);

        return total.count();
    }

    void benchmark_scene_multiple_times(int amount_of_repeats=10, string msg="render", bool print_progress=false) {
        vector<long> data;
        for (int i = 0; i < amount_of_repeats; i++) {
            data.push_back(benchmark_scene());
            if (print_progress) {
                cout << static_cast<int>((static_cast<float>(i + 1) / static_cast<float>(amount_of_repeats)) * 100) << "%" << endl;
            }
        }
        append_to_file(scene_benchmark_path,msg, data);
    }

    long benchmark_vec_add() {
        Vec v(1, 2, 3), u(4, 5, 6), w;
//        VecOptimized v(1, 2, 3), u(4, 5, 6), w;

        auto start = high_resolution_clock::now();
        w = u + v;
        auto stop = high_resolution_clock::now();
        auto total = duration_cast<nanoseconds>(stop - start);

        return total.count();
    }


    void benchmark_vec_multiple_times(int amount_of_repeats=1000, string msg="vec", bool print_progress=false) {
        vector<long> data;
        for (int i = 0; i < amount_of_repeats; i++) {
            data.push_back(benchmark_vec_add());
            if (print_progress) {
                cout << static_cast<int>((static_cast<float>(i + 1) / static_cast<float>(amount_of_repeats)) * 100) << "%" << endl;
            }
        }
        append_to_file(vec_benchmark_path, msg, data, false);
    }
};

#endif //DMITRYC_RAYTRACER_PERFORMANCE_TESTING_H

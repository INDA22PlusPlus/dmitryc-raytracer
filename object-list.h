
#ifndef DMITRYC_RAYTRACER_OBJECT_LIST_H
#define DMITRYC_RAYTRACER_OBJECT_LIST_H

#include <utility>
#include <vector>
#include <memory>
#include "object.h"

using namespace std;

// Highly inspired by the guide because I don't have much experience with this sort of lists
class ObjectList: public Object {
public:
    vector<shared_ptr<Object>> objects;

    ObjectList() = default;

    // Todo: Right referencing?
    explicit ObjectList(const shared_ptr<Object>& object) {
        add(object);
    }

    // Todo: Right referencing?
    void add(const shared_ptr<Object>& object) {
        objects.push_back(object);
    }

    void clear() {
        objects.clear();
    }

    bool hit(Ray& ray, HitData& hit_data) override {
        HitData temp_hit_data;
        bool hit = false;
        double closest_so_far = t_max;

        for (const auto& object : objects) {
            object->t_max = closest_so_far;
            if (object->hit(ray, temp_hit_data)) {
                hit = true;
                closest_so_far = temp_hit_data.t;
                hit_data = temp_hit_data;
            }
        }

        return hit;
    }
};

#endif //DMITRYC_RAYTRACER_OBJECT_LIST_H

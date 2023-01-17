//
// Created by chiri on 2023-01-17.
//

#ifndef DMITRYC_RAYTRACER_CAMERA_H
#define DMITRYC_RAYTRACER_CAMERA_H

#include "vec.h"

// Todo: Implement different coordinate systems
class Camera {
public:
    double height;
    double width;
    double focal_length;

    Point origin;
    Vec horizontal;
    Vec vertical;
    Point lower_left_corner;

    // Todo: Calling the other constructor safe?
    Camera() {
        double aspect_ratio = 16.0 / 9.0;

        // Total height and width
        height = 2.0;
        width = aspect_ratio * height;

        origin = Point(0, 0, 0);
        // Distance from origin to camera plane
        focal_length = 1.0;

        // Coordinate system in use: Y-axis points up, X-axis to the right and Z-axis forward in the right-handed system
        // Horizontal and Vertical are chosen with respect to the coordinate system, in this case horizontal points
        // at positive X and vertical at positive Y
        horizontal = Vec(width, 0, 0);
        vertical = Vec(0, height, 0);
        lower_left_corner = origin - horizontal/2 - vertical/2 - Vec(0, 0, focal_length);
    }

    explicit Camera(double aspect_ratio) {
        height = 2.0;
        width = aspect_ratio * height;
        focal_length = 1.0;

        // Coordinate system in use: y points up, x to the right and z forward in the right-handed system
        origin = Point(0, 0, 0);
        horizontal = Vec(width, 0, 0);
        vertical = Vec(0, height, 0);
        lower_left_corner = origin - horizontal/2 - vertical/2 - Vec(0, 0, focal_length);
    }
};

#endif //DMITRYC_RAYTRACER_CAMERA_H

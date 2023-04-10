#pragma once

#include "vec3.h"
#include "util.h"
#include <iostream>

void writeColor(std::ostream& out, color pixel_color, int samplesNum) {

    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Divide the color by the number of samples.
    double scale = 1.0 / samplesNum;

    // gamma-correct for gamma=2.0.
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    util util;
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * util.clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * util.clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * util.clamp(b, 0.0, 0.999)) << '\n';
}
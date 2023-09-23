#pragma once

#include "geometry.hpp"
#include <cstdint>

namespace picocanvas {
    struct Bitmap {
        const uint16_t *data;
        const uint16_t width;
        const uint16_t height;

        Bitmap(const uint16_t *data, uint16_t width, uint16_t height) : data(data), width(width), height(height) {}

        Rect rect() const {
            return Rect{0, 0, width, height};
        }

        uint16_t sample_color(uint16_t x, uint16_t y) const {
            return data[y * width + x];
        }
    };
}
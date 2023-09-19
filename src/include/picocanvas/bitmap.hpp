#pragma once

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
    };
}
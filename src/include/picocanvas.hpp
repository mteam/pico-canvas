#pragma once

#include <cstdint>
#include <array>
#include "picocanvas/geometry.hpp"

namespace picocanvas {
    class Canvas {
    public:
        Canvas(uint16_t width, uint16_t height);

        void fill(uint16_t color) {
            fill_rect(bounds, color);
        }

        void fill_rect(const Rect &rect, uint16_t color);

    protected:
        uint16_t *frame_buffer;
        Rect bounds;
    };
}
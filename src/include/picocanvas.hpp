#pragma once

#include <cstdint>
#include <array>
#include "picocanvas/geometry.hpp"

namespace picocanvas {
    class Canvas {
    public:
        Canvas(uint16_t width, uint16_t height);

    protected:
        uint16_t *frame_buffer;
        Rect bounds;
    };
}
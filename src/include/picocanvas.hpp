#pragma once

#include <cstdint>
#include <array>
#include <cstddef>
#include "picocanvas/geometry.hpp"
#include "picocanvas/bitmap.hpp"

namespace picocanvas {
    class Canvas {
    public:
        Canvas(uint16_t width, uint16_t height);

        uint16_t *get_frame_buffer() { return frame_buffer; }

        void fill(uint16_t color) {
            fill_rect(bounds, color);
        }

        void fill_rect(const Rect &rect, uint16_t color);

        void draw_bitmap(const Bitmap &bitmap, const Point &dest);
        void draw_bitmap(const Bitmap &bitmap, const Point &dest, const Rect &src);

    protected:
        uint16_t *frame_buffer;
        Rect bounds;
    };
}
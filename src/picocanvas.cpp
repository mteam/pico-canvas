#include "picocanvas.hpp"

namespace picocanvas {
    Canvas::Canvas(uint16_t width, uint16_t height) : bounds(0, 0, width, height) {
        frame_buffer = new uint16_t[width * height];
    }

    void Canvas::fill_rect(const Rect &rect, uint16_t color) {
        for (int y = rect.y; y < (rect.y + rect.h); y++) {
            for (int x = rect.x; x < (rect.x + rect.w); x++) {
                frame_buffer[y * bounds.w + x] = color;
            }
        }
    }
}

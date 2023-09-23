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

    void Canvas::draw_bitmap(const Bitmap &bitmap, const Point &dest) {
        draw_bitmap(bitmap, dest, bitmap.rect());
    }

    void Canvas::draw_bitmap(const Bitmap &bitmap, const Point &dest, const Rect &src) {
        auto drawn = bitmap.rect().intersection(src);

        for (int y = 0; y < drawn.h; y++) {
            for (int x = 0; x < drawn.w; x++) {
                uint16_t col = bitmap.data[(drawn.y + y) * bitmap.width + (drawn.x + x)];
                if (col == state.bitmap_transparency) continue;

                frame_buffer[(dest.y + y) * bounds.w + (dest.x + x)] = col;
            }
        }
    }

    void Canvas::stroke_rect(const Rect &rect, uint16_t color) {
        horizontal_line({rect.x, rect.y}, rect.w, color);
        horizontal_line({rect.x, rect.y + rect.h - 1}, rect.w, color);
        vertical_line({rect.x, rect.y}, rect.h, color);
        vertical_line({rect.x + rect.w - 1, rect.y}, rect.h, color);
    }
}

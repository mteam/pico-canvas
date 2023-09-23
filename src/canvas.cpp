#include "picocanvas.hpp"

namespace picocanvas {
    Canvas::Canvas(uint16_t width, uint16_t height) : bounds(0, 0, width, height) {
        frame_buffer = new uint16_t[width * height];
    }

    void Canvas::fill_rect(const Rect &rect, uint16_t color) {
        for (int y = rect.y; y < (rect.y + rect.h); y++) {
            for (int x = rect.x; x < (rect.x + rect.w); x++) {
                frame_buffer[y * bounds.w + x] = color & state.color_mask;
            }
        }
    }

    template<class T>
    void Canvas::draw_bitmap(const T &bitmap, const Point &dest) {
        Rect src = bitmap.rect();
        draw_bitmap(bitmap, dest, src);
    }

    template void Canvas::draw_bitmap(const Bitmap16 &, const picocanvas::Point &);
    template void Canvas::draw_bitmap(const Bitmap1 &, const picocanvas::Point &);

    template<class T>
    void Canvas::draw_bitmap(const T &bitmap, const Point &dest, const Rect &src) {
        picocanvas::Rect rect = bitmap.rect();
        auto drawn = rect.intersection(src);

        for (int y = 0; y < drawn.h; y++) {
            for (int x = 0; x < drawn.w; x++) {
                uint16_t col = bitmap.sample_color(drawn.x + x, drawn.y + y);
                if (col == state.bitmap_transparency) continue;

                frame_buffer[(dest.y + y) * bounds.w + (dest.x + x)] = col & state.color_mask;
            }
        }
    }

    template void Canvas::draw_bitmap(const Bitmap16 &, const picocanvas::Point &, const picocanvas::Rect &);
    template void Canvas::draw_bitmap(const Bitmap1 &, const picocanvas::Point &, const picocanvas::Rect &);

    void Canvas::stroke_rect(const Rect &rect, uint16_t color) {
        horizontal_line({rect.x, rect.y}, rect.w, color);
        horizontal_line({rect.x, rect.y + rect.h - 1}, rect.w, color);
        vertical_line({rect.x, rect.y}, rect.h, color);
        vertical_line({rect.x + rect.w - 1, rect.y}, rect.h, color);
    }
}

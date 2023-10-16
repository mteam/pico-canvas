#include "picocanvas.hpp"

namespace picocanvas {
    Canvas::Canvas(uint16_t width, uint16_t height) : bounds(0, 0, width, height) {
        frame_buffer = new uint16_t[width * height];

        state = {
            .bitmap_transparency = 0x0000,
            .color_mask = 0xffff,
            .clip = bounds
        };
    }

    void Canvas::fill_rect(const Rect &rect, uint16_t color) {
        Rect drawn = rect.intersection(state.clip);

        for (int y = drawn.y; y < (drawn.y + drawn.h); y++) {
            for (int x = drawn.x; x < (drawn.x + drawn.w); x++) {
                set_pixel_raw({x, y}, color);
            }
        }
    }

    template<class T>
    void Canvas::draw_bitmap(const T &bitmap, const Point &dest, int scale) {
        Rect src = bitmap.rect();
        draw_bitmap(bitmap, dest, src, scale);
    }

    template void Canvas::draw_bitmap(const Bitmap1 &, const picocanvas::Point &, int);
    template void Canvas::draw_bitmap(const BitmapBMP &, const picocanvas::Point &, int);

    template<class T>
    void Canvas::draw_bitmap(const T &bitmap, const Point &dest, const Rect &src, int scale) {
        Rect bitmap_bounds = bitmap.rect();
        Rect drawn = src.intersection(bitmap_bounds);

        for (int y = 0; y < drawn.h; y++) {
            for (int x = 0; x < drawn.w; x++) {
                uint16_t col = bitmap.sample_color(drawn.x + x, drawn.y + y);
                if (col == state.bitmap_transparency) continue;

                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        set_pixel_clip({dest.x + x * scale + sx, dest.y + y * scale + sy}, col);
                    }
                }
            }
        }
    }

    template void Canvas::draw_bitmap(const Bitmap1 &, const picocanvas::Point &, const picocanvas::Rect &, int);
    template void Canvas::draw_bitmap(const BitmapBMP &, const picocanvas::Point &, const picocanvas::Rect &, int);

    void Canvas::stroke_rect(const Rect &rect, uint16_t color) {
        horizontal_line({rect.x, rect.y}, rect.w, color);
        horizontal_line({rect.x, rect.y + rect.h - 1}, rect.w, color);
        vertical_line({rect.x, rect.y}, rect.h, color);
        vertical_line({rect.x + rect.w - 1, rect.y}, rect.h, color);
    }
}

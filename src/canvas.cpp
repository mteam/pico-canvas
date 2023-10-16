#include "picocanvas.hpp"

namespace picocanvas {
    Canvas::Canvas(uint16_t width, uint16_t height) : bounds(0, 0, width, height) {
        frame_buffer = new uint8_t[width * height];

        state = {
            .bitmap_transparency = 0x00,
            .color_mask = 0xff,
            .clip = bounds
        };
    }

    void Canvas::fill_rect(const Rect &rect, uint8_t color) {
        Rect drawn = rect.intersection(state.clip);

        int index = drawn.y * bounds.w + drawn.x; // index of the first pixel to draw
        int step = bounds.w - drawn.w; // number of pixels to skip to get to the next row

        for (int h = 0; h < drawn.h; h++) {
            for (int w = 0; w < drawn.w; w++) {
                set_pixel_raw(index++, color);
            }
            index += step;
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

        Point dest_clip = dest;
        Rect src_clip = src.intersection(bitmap_bounds);
        clip_bitmap(dest_clip, src_clip, scale);

        int index = dest_clip.y * bounds.w + dest_clip.x; // index of the first pixel to draw
        int step = bounds.w - src_clip.w * scale; // number of pixels to skip to get to the next row

        for (int y = 0; y < src_clip.h; y++) {
            for (int sy = 0; sy < scale; sy++) {
                for (int x = 0; x < src_clip.w; x++) {
                    uint8_t col = bitmap.sample_color(src_clip.x + x, src_clip.y + y);

                    for (int sx = 0; sx < scale; sx++) {
                        if (col != state.bitmap_transparency) {
                            set_pixel_raw(index, col);
                        }
                        index++;
                    }
                }
                index += step;
            }
        }
    }

    template void Canvas::draw_bitmap(const Bitmap1 &, const picocanvas::Point &, const picocanvas::Rect &, int);
    template void Canvas::draw_bitmap(const BitmapBMP &, const picocanvas::Point &, const picocanvas::Rect &, int);

    void Canvas::clip_bitmap(Point &dest, Rect &src, int scale) {
        if (dest.x < 0) {
            src.x -= dest.x / scale;
            src.w += dest.x / scale;
            dest.x = 0;
        }

        if (dest.y < 0) {
            src.y -= dest.y / scale;
            src.h += dest.y / scale;
            dest.y = 0;
        }

        if (dest.x + src.w * scale > bounds.w) {
            src.w = (bounds.w - dest.x) / scale;
        }

        if (dest.y + src.h * scale > bounds.h) {
            src.h = (bounds.h - dest.y) / scale;
        }
    }

    void Canvas::stroke_rect(const Rect &rect, uint8_t color) {
        horizontal_line({rect.x, rect.y}, rect.w, color);
        horizontal_line({rect.x, rect.y + rect.h - 1}, rect.w, color);
        vertical_line({rect.x, rect.y}, rect.h, color);
        vertical_line({rect.x + rect.w - 1, rect.y}, rect.h, color);
    }
}

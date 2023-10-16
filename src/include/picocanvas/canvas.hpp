#pragma once

#include <cstdint>
#include "picocanvas/geometry.hpp"
#include "picocanvas/bitmap.hpp"

namespace picocanvas {
    struct CanvasState {
        uint8_t bitmap_transparency{};
        uint8_t color_mask{};
        Rect clip;
    };

    class Canvas {
    public:
        CanvasState state;

        Canvas(uint16_t width, uint16_t height);

        uint8_t *get_frame_buffer() { return frame_buffer; }

        void set_pixel_clip(const Point &p, uint8_t color) {
            if (state.clip.contains(p)) set_pixel_raw(p, color);
        }

        void set_pixel_raw(const Point &p, uint8_t color) {
            frame_buffer[p.y * bounds.w + p.x] = color & state.color_mask;
        }

        void set_pixel_raw(int index, uint8_t color) {
            frame_buffer[index] = color & state.color_mask;
        }

        void fill(uint8_t color) {
            fill_rect(bounds, color);
        }

        void fill_rect(const Rect &rect, uint8_t color);

        void horizontal_line(const Point &p, int w, uint8_t color) {
            fill_rect({p.x, p.y, w, 1}, color);
        }

        void vertical_line(const Point &p, int h, uint8_t color) {
            fill_rect({p.x, p.y, 1, h}, color);
        }

        void stroke_rect(const Rect &rect, uint8_t color);

        template<class T>
        void draw_bitmap(const T &bitmap, const Point &dest, int scale = 1);

        template<class T>
        void draw_bitmap(const T &bitmap, const Point &dest, const Rect &src, int scale = 1);

    protected:
        uint8_t *frame_buffer;
        Rect bounds;
    };
}

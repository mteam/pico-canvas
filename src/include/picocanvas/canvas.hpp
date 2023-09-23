#pragma once

#include <cstdint>
#include "picocanvas/geometry.hpp"
#include "picocanvas/bitmap.hpp"

namespace picocanvas {
    struct CanvasState {
        uint16_t bitmap_transparency{};
        uint16_t color_mask{};
        Rect clip;
    };

    class Canvas {
    public:
        CanvasState state;

        Canvas(uint16_t width, uint16_t height);

        uint16_t *get_frame_buffer() { return frame_buffer; }

        inline void set_pixel(const Point &p, uint16_t color);

        void fill(uint16_t color) {
            fill_rect(bounds, color);
        }

        void fill_rect(const Rect &rect, uint16_t color);

        void horizontal_line(const Point &p, int w, uint16_t color) {
            fill_rect({p.x, p.y, w, 1}, color);
        }

        void vertical_line(const Point &p, int h, uint16_t color) {
            fill_rect({p.x, p.y, 1, h}, color);
        }

        void stroke_rect(const Rect &rect, uint16_t color);

        template<class T>
        void draw_bitmap(const T &bitmap, const Point &dest);

        template<class T>
        void draw_bitmap(const T &bitmap, const Point &dest, const Rect &src);

    protected:
        uint16_t *frame_buffer;
        Rect bounds;
    };
}

#pragma once

#include <string>
#include <cstdint>
#include "picocanvas/bitmap.hpp"
#include "picocanvas/geometry.hpp"
#include "picocanvas/canvas.hpp"

namespace picocanvas {
    class FixedWidthFont {
    public:
        FixedWidthFont(Bitmap1 font_bitmap,
                       int16_t character_width,
                       int16_t character_height) : font_bitmap(font_bitmap),
                                                   character_width(character_width),
                                                   character_height(character_height) {}

        Rect measure_text(const std::string &text) const;
        Rect measure_text(int length) const;

        void write_text(Canvas &canvas, const std::string &text, const Point &position, uint16_t color);

    private:
        const int16_t character_height;
        const int16_t character_width;
        Bitmap1 font_bitmap;

        void write_character(Canvas &canvas, char character, const Point &position);
    };
}
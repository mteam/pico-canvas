#pragma once

#include <string>
#include <cstdint>
#include "picocanvas/bitmap.hpp"
#include "picocanvas/geometry.hpp"
#include "picocanvas/canvas.hpp"

namespace picocanvas {
    class FixedWidthFont {
    public:
        FixedWidthFont(const Bitmap1 &font_bitmap,
                       int16_t character_width,
                       int16_t character_height) : font_bitmap(font_bitmap),
                                                   character_width(character_width),
                                                   character_height(character_height) {}

        Rect measure_text(const std::string &text) const;

        void write_text(Canvas &canvas, const std::string &text, const Point &position, uint16_t color) const;

    private:
        const int16_t character_height;
        const int16_t character_width;
        const Bitmap1 &font_bitmap;

        void write_character(Canvas &canvas, char character, const Point &position) const;
    };
}
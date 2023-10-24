#include "picocanvas/text.hpp"

picocanvas::Rect picocanvas::FixedWidthFont::measure_text(const std::string &text) const {
    return measure_text(text.length());
}

picocanvas::Rect picocanvas::FixedWidthFont::measure_text(int length) const {
    int16_t width = length * character_width;
    int16_t height = character_height;
    return {0, 0, width, height};
}

void picocanvas::FixedWidthFont::write_text(picocanvas::Canvas &canvas,
                                            const std::string &text,
                                            const picocanvas::Point &position,
                                            uint16_t color) {
    auto prev_state = canvas.state;
    canvas.state.color_mask = color;

    for (int i = 0; i < text.length(); i++) {
        write_character(canvas, text[i], {position.x + i * character_width, position.y});
    }

    canvas.state = prev_state;
}

void picocanvas::FixedWidthFont::write_character(picocanvas::Canvas &canvas,
                                                 char character,
                                                 const picocanvas::Point &position) {
    uint8_t index = character;
    Rect src = {0, index * character_height, character_width, character_height};

    canvas.draw_bitmap(font_bitmap, position, src);
}

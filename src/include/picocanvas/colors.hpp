#pragma once

#include <cstdint>

namespace picocanvas {
    constexpr inline uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
        return (r >> 3) << 11 | (g >> 2) << 5 | (b >> 3);
    }
}
#include <algorithm>
#include "picocanvas/geometry.hpp"

namespace picocanvas {
    Point Point::clamp(const Rect &r) const {
        return {
                std::min(std::max(x, r.x), r.x + r.w),
                std::min(std::max(y, r.y), r.y + r.h)
        };
    }

    Rect Rect::intersection(const Rect &r) const {
        return {std::max(x, r.x),
                std::max(y, r.y),
                std::min(x + w, r.x + r.w) - std::max(x, r.x),
                std::min(y + h, r.y + r.h) - std::max(y, r.y)};
    }

    void Rect::inflate(int32_t v) {
        x -= v;
        y -= v;
        w += v * 2;
        h += v * 2;
    }

    void Rect::deflate(int32_t v) {
        x += v;
        y += v;
        w -= v * 2;
        h -= v * 2;
    }
}
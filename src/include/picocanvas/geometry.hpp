#pragma once

#include <cstdint>

namespace picocanvas {
    struct Rect;

    struct Point {
        int32_t x = 0, y = 0;

        Point() = default;

        Point(int32_t x, int32_t y) : x(x), y(y) {}

        inline Point &operator-=(const Point &a) {
            x -= a.x;
            y -= a.y;
            return *this;
        }

        inline Point &operator+=(const Point &a) {
            x += a.x;
            y += a.y;
            return *this;
        }

        inline Point &operator/=(const int32_t a) {
            x /= a;
            y /= a;
            return *this;
        }

        Point clamp(const Rect &r) const;
    };

    inline bool operator==(const Point &lhs, const Point &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }

    inline bool operator!=(const Point &lhs, const Point &rhs) { return !(lhs == rhs); }

    inline Point operator-(Point lhs, const Point &rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline Point operator-(const Point &rhs) { return Point(-rhs.x, -rhs.y); }

    inline Point operator+(Point lhs, const Point &rhs) {
        lhs += rhs;
        return lhs;
    }

    inline Point operator/(Point lhs, const int32_t a) {
        lhs /= a;
        return lhs;
    }

    struct Rect {
        int32_t x = 0, y = 0, w = 0, h = 0;

        Rect() = default;

        Rect(int32_t x, int32_t y, int32_t w, int32_t h) : x(x), y(y), w(w), h(h) {}

        Rect(const Point &tl, const Point &br) : x(tl.x), y(tl.y), w(br.x - tl.x), h(br.y - tl.y) {}

        bool empty() const;

        bool contains(const Point &p) const;

        bool contains(const Rect &p) const;

        bool intersects(const Rect &r) const;

        Rect intersection(const Rect &r) const;

        void inflate(int32_t v);

        void deflate(int32_t v);
    };
}

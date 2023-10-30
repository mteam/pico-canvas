#pragma once

#include "geometry.hpp"
#include "colors.hpp"
#include <cstdint>
#include <cstddef>
#include <vector>

namespace picocanvas {
    struct Bitmap1 {
        const uint8_t *data;
        const uint16_t width;
        const uint16_t height;

        unsigned int cursor = 0;

        Bitmap1(const uint8_t *data, uint16_t width, uint16_t height) : data(data), width(width), height(height) {}

        Rect rect() const {
            return Rect{0, 0, width, height};
        }

        void set_cursor(uint16_t x, uint16_t y) {
            cursor = y * width + x;
        }

        uint8_t sample_color() const {
            // return n-th bit of data
            uint8_t value = (data[cursor / 8] >> (7 - cursor % 8)) & 1;

            // return black or white
            return value ? 0xFF : 0x00;
        }

        uint8_t sample_color(uint16_t x, uint16_t y) {
            set_cursor(x, y);
            return sample_color();
        }
    };

#pragma pack(push, 1)
    struct BMPHeader {
        uint16_t signature;
        uint32_t file_size;
        uint32_t reserved;
        uint32_t data_offset;
    };

    struct DIBHeader {
        uint32_t header_size;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        uint32_t x_pixels_per_meter;
        uint32_t y_pixels_per_meter;
        uint32_t colors_used;
        uint32_t colors_important;
    };

    struct BMPColor {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    };
#pragma pack(pop)

    struct BitmapBMP {
        const uint8_t *data;
        uint32_t cursor = 0;

        BitmapBMP(const uint8_t *data, std::size_t length) : data(data) {}

        explicit BitmapBMP(std::vector<uint8_t> data) : BitmapBMP(data.data(), data.size()) {}

        Rect rect() const {
            return Rect{0, 0, static_cast<int32_t>(dib_header()->width), static_cast<int32_t>(dib_header()->height)};
        }

        std::vector<BMPColor> palette_vector() const {
            std::vector<BMPColor> palette_vector;
            palette_vector.reserve(dib_header()->colors_used);

            for (int i = 0; i < dib_header()->colors_used; i++) {
                palette_vector.push_back(palette()[i]);
            }

            return palette_vector;
        }

        void set_cursor(uint16_t x, uint16_t y) {
            // BMPs are stored upside down
            y = dib_header()->height - y - 1;

            uint8_t bytes_per_pixel = dib_header()->bits_per_pixel / 8;
            uint32_t row_size = (dib_header()->width * bytes_per_pixel + 3) & -4;
            cursor = y * row_size + x;
        }

        uint8_t sample_color() const {
            if (dib_header()->bits_per_pixel == 8) {
                return pixels()[cursor];
            } else {
                return 0;
            }
        }

        uint8_t sample_color(uint16_t x, uint16_t y) {
            set_cursor(x, y);
            return sample_color();
        }
    private:
        inline const BMPHeader *bmp_header() const {
            return reinterpret_cast<const BMPHeader *>(data);
        }

        inline const DIBHeader *dib_header() const {
            return reinterpret_cast<const DIBHeader *>(data + sizeof(BMPHeader));
        }

        inline const BMPColor *palette() const {
            return reinterpret_cast<const BMPColor *>(data + sizeof(BMPHeader) + dib_header()->header_size);
        }

        inline const uint8_t *pixels() const {
            return data + bmp_header()->data_offset;
        }
    };
}
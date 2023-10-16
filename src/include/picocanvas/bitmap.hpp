#pragma once

#include "geometry.hpp"
#include "colors.hpp"
#include <cstdint>
#include <cstddef>

namespace picocanvas {
    struct Bitmap1 {
        const uint8_t *data;
        const uint16_t width;
        const uint16_t height;

        Bitmap1(const uint8_t *data, uint16_t width, uint16_t height) : data(data), width(width), height(height) {}

        Rect rect() const {
            return Rect{0, 0, width, height};
        }

        uint8_t sample_color(uint16_t x, uint16_t y) const {
            uint16_t n = y * width + x;

            // return n-th bit of data
            uint8_t value = (data[n / 8] >> (7 - n % 8)) & 1;

            // return black or white
            return value ? 0xFF : 0x00;
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
        const BMPHeader *bmp_header;
        const DIBHeader *dib_header;
        const BMPColor *palette;
        const void *pixels;
        const std::size_t length;

        BitmapBMP(const uint8_t *data, std::size_t length) :
                data(data),
                bmp_header(reinterpret_cast<const BMPHeader *>(data)),
                dib_header(reinterpret_cast<const DIBHeader *>(data + sizeof(BMPHeader))),
                palette(reinterpret_cast<const BMPColor *>(data + sizeof(BMPHeader) + dib_header->header_size)),
                pixels(data + bmp_header->data_offset),
                length(length) {}

        Rect rect() const {
            return Rect{0, 0, static_cast<int32_t>(dib_header->width), static_cast<int32_t>(dib_header->height)};
        }

        uint8_t sample_color(uint16_t x, uint16_t y) const {
            // BMPs are stored upside down
            y = dib_header->height - y - 1;

            if (dib_header->bits_per_pixel == 8) {
                auto *pixels8 = reinterpret_cast<const uint8_t *>(pixels);
                return pixels8[y * dib_header->width + x];
            } else {
                return 0;
            }
        }
    };
}
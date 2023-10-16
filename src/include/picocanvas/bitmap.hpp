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

        uint16_t sample_color(uint16_t x, uint16_t y) const {
            uint16_t n = y * width + x;

            // return n-th bit of data
            uint8_t value = (data[n / 8] >> (7 - n % 8)) & 1;

            // return black or white
            return value ? 0xFFFF : 0x0000;
        }
    };

#pragma pack(push, 1)
    struct BMPHeader {
        uint16_t signature;
        uint32_t file_size;
        uint32_t reserved;
        uint32_t data_offset;
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
#pragma pack(pop)

    struct BitmapBMP {
        const uint8_t *data;
        const std::size_t length;

        BitmapBMP(const uint8_t *data, std::size_t length) : data(data), length(length) {}

        Rect rect() const {
            auto *header = (BMPHeader *) data;

            return Rect{0, 0, static_cast<int32_t>(header->width), static_cast<int32_t>(header->height)};
        }

        uint16_t sample_color(uint16_t x, uint16_t y) const {
            auto *header = reinterpret_cast<const BMPHeader *>(data);
            auto *dib = reinterpret_cast<const uint8_t *>(&header->header_size);

            // BMPs are stored upside down
            y = header->height - y - 1;

            if (header->bits_per_pixel == 8) {
                auto *palette = dib + header->header_size;
                auto *pixels = data + header->data_offset;

                uint8_t index = pixels[y * header->width + x];

                uint8_t r = palette[index * 4 + 2];
                uint8_t g = palette[index * 4 + 1];
                uint8_t b = palette[index * 4 + 0];

                return rgb565(r, g, b);
            } else if (header->bits_per_pixel == 16) {
                auto *pixels = reinterpret_cast<const uint16_t *>(data + header->data_offset);

                return pixels[y * header->width + x];
            } else if (header->bits_per_pixel == 24) {
                auto *pixels = data + header->data_offset;

                uint8_t r = pixels[(y * header->width + x) * 3 + 2];
                uint8_t g = pixels[(y * header->width + x) * 3 + 1];
                uint8_t b = pixels[(y * header->width + x) * 3 + 0];

                return rgb565(r, g, b);
            } else {
                return 0;
            }
        }
    };
}
#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>
#include "AABB.h"
#include "Color.h"
namespace lcg
{
    inline lcg::Color get_pixel_from_buffer(const std::vector<uint8_t> &data, uint32_t width, uint32_t height, int x, int y)
    {
        lcg::Color color{};
        if (x < 0 || y < 0 || x >= (int)width || y >= (int)height)
        {
            return color;
        }
        const size_t idx = (static_cast<size_t>(y) * width + static_cast<size_t>(x)) * 3;
        color.r = data[idx + 0];
        color.g = data[idx + 1];
        color.b = data[idx + 2];
        return color;
    }

    inline void set_pixel_to_buffer(std::vector<uint8_t> &data, uint32_t width, uint32_t height, int x, int y, uint8_t r, uint8_t g, uint8_t b)
    {
        if (x < 0 || y < 0 || x >= (int)width || y >= (int)height)
        {
            return;
        }
        const size_t idx = (static_cast<size_t>(y) * width + static_cast<size_t>(x)) * 3;
        data[idx + 0] = r;
        data[idx + 1] = g;
        data[idx + 2] = b;
    }

    void draw_old_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
    {
        uint32_t width = 300;
        uint32_t height = 300;

        lcg::PPM ppm(".", "old_line", width, height);

        float k = (float)(y1 - y0) / (x1 - x0);
        std::vector<uint8_t> data(width * height * 3, 0);

        for (uint32_t x = x0; x <= x1; ++x)
        {
            uint32_t y = static_cast<uint32_t>(k * (x - x0) + y0);

            data[(y * width + x) * 3 + 0] = 255; // R
            data[(y * width + x) * 3 + 1] = 255; // G
            data[(y * width + x) * 3 + 2] = 255; // B
        }

        ppm.setData(data);
        std::cout << "创建 old_line.ppm 成功" << std::endl;
    }

    void draw_dda_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
    {
        uint32_t width = 300;
        uint32_t height = 300;

        lcg::PPM ppm(".", "dda_line", width, height);
        std::vector<uint8_t> data(width * height * 3, 0);

        int dx = (int)x1 - (int)x0;
        int dy = (int)y1 - (int)y0;

        int steps = std::max(abs(dx), abs(dy));

        float x_inc = dx / (float)steps;
        float y_inc = dy / (float)steps;

        float x = x0;
        float y = y0;

        for (int i = 0; i <= steps; ++i)
        {
            int xi = (int)std::round(x);
            int yi = (int)std::round(y);

            if (xi >= 0 && xi < width && yi >= 0 && yi < height)
            {
                data[(yi * width + xi) * 3 + 0] = 255;
                data[(yi * width + xi) * 3 + 1] = 255;
                data[(yi * width + xi) * 3 + 2] = 255;
            }

            x += x_inc;
            y += y_inc;
        }

        ppm.setData(data);
        std::cout << "创建 dda_line.ppm 成功" << std::endl;
    }
    void draw_bersenham_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
    {
        const uint32_t width = 300;
        const uint32_t height = 300;

        lcg::PPM ppm(".", "bresenham", width, height);
        std::vector<uint8_t> data(width * height * 3, 0);

        // 计算方向
        int dx = std::abs((int)x1 - (int)x0);
        int dy = std::abs((int)y1 - (int)y0);

        // 确定步进方向
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;

        // 初始误差项
        int err = dx - dy;

        int x = (int)x0;
        int y = (int)y0;

        while (true)
        {
            if (x >= 0 && x < (int)width && y >= 0 && y < (int)height)
            {
                data[(y * width + x) * 3 + 0] = 255;
                data[(y * width + x) * 3 + 1] = 255;
                data[(y * width + x) * 3 + 2] = 255;
            }

            if (x == (int)x1 && y == (int)y1)
                break;

            int e2 = 2 * err;

            if (e2 > -dy)
            {
                err -= dy;
                x += sx;
            }

            if (e2 < dx)
            {
                err += dx;
                y += sy;
            }
        }

        ppm.setData(data);
        std::cout << "创建 bresenham.ppm 成功" << std::endl;
    }

    AABB computeAABB(const lcg::Vec2 &A, const lcg::Vec2 &B, const lcg::Vec2 &C)
    {
        AABB box;
        box.min.x = std::min({A.x, B.x, C.x});
        box.min.y = std::min({A.y, B.y, C.y});
        box.max.x = std::max({A.x, B.x, C.x});
        box.max.y = std::max({A.y, B.y, C.y});
        return box;
    }
    void draw_triangle_with_ssaa(std::vector<uint8_t> &data, uint32_t width, uint32_t height, lcg::Vec2 A, lcg::Vec2 B, lcg::Vec2 C, lcg::Color color, const int ssaa_factor = 4)
    {
        AABB box = computeAABB(A, B, C);

        lcg::Vec2 AB = B - A;
        lcg::Vec2 BC = C - B;
        lcg::Vec2 CA = A - C;
        for (int y = (int)box.min.y; y <= (int)box.max.y; ++y)
        {
            for (int x = (int)box.min.x; x <= (int)box.max.x; ++x)
            {
                int inside_count = 0;
                for (int i = 0; i < ssaa_factor; i++)
                {
                    for (int j = 0; j < ssaa_factor; j++)
                    {
                        float sx = (float)x + (i + 0.5f) / ssaa_factor;
                        float sy = (float)y + (j + 0.5f) / ssaa_factor;
                        lcg::Vec2 P(sx, sy);

                        lcg::Vec2 AP = P - A;
                        lcg::Vec2 BP = P - B;
                        lcg::Vec2 CP = P - C;

                        float cross1 = AB.cross(AP);
                        float cross2 = BC.cross(BP);
                        float cross3 = CA.cross(CP);

                        if ((cross1 >= 0 && cross2 >= 0 && cross3 >= 0) ||
                            (cross1 <= 0 && cross2 <= 0 && cross3 <= 0))
                        {
                            inside_count++;
                        }
                    }
                }
                if (inside_count > 0)
                {
                    float coverage = (float)inside_count / (ssaa_factor * ssaa_factor);

                    lcg::Color background = get_pixel_from_buffer(data, width, height, x, y);

                    Color final_color;
                    final_color.r = (uint8_t)(color.r * coverage + background.r * (1.0f - coverage));
                    final_color.g = (uint8_t)(color.g * coverage + background.g * (1.0f - coverage));
                    final_color.b = (uint8_t)(color.b * coverage + background.b * (1.0f - coverage));

                    set_pixel_to_buffer(data, width, height, x, y, final_color.r, final_color.g, final_color.b);
                }
            }
        }
    }
}

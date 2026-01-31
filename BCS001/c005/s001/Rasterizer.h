#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
namespace lcg
{
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
}
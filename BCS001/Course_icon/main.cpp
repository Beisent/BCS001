#include <algorithm>
#include <iostream>
#include <vector>
#include "ppm.h"

int main()
{
    const uint32_t width = 25;
    const uint32_t height = 25;
    lcg::PPM image(".", "test_image", width, height);
    std::vector<uint8_t> data(width * height * 3, 255);
    // 矩形位置 (左上角和右下角)
    uint32_t x0 = 1, y0 = 1;
    uint32_t x1 = 23, y1 = 23;
    auto setPixel = [&](uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
    {
        data[(y * width + x) * 3 + 0] = r;
        data[(y * width + x) * 3 + 1] = g;
        data[(y * width + x) * 3 + 2] = b;
    };

    // 定义四个角的颜色41, 163, 227
    uint8_t r_tl = 80, g_tl = 160, b_tl = 255; // 左上
    uint8_t r_tr = 30, g_tr = 124, b_tr = 187; // 右上
    uint8_t r_br = 0, g_br = 0, b_br = 0;  // 右下
    uint8_t r_bl = 30, g_bl = 124, b_bl = 187;  // 左下

    // 上边
    for (uint32_t x = x0; x <= x1; x++)
    {
        float t = float(x - x0) / float(x1 - x0);
        uint8_t r = uint8_t(r_tl + t * (r_tr - r_tl));
        uint8_t g = uint8_t(g_tl + t * (g_tr - g_tl));
        uint8_t b = uint8_t(b_tl + t * (b_tr - b_tl));
        setPixel(x, y0, r, g, b);
    }

    // 右边
    for (uint32_t y = y0; y <= y1; y++)
    {
        float t = float(y - y0) / float(y1 - y0);
        uint8_t r = uint8_t(r_tr + t * (r_br - r_tr));
        uint8_t g = uint8_t(g_tr + t * (g_br - g_tr));
        uint8_t b = uint8_t(b_tr + t * (b_br - b_tr));
        setPixel(x1, y, r, g, b);
    }

    // 下边
    for (uint32_t x = x1; x >= x0; x--)
    {
        float t = float(x1 - x) / float(x1 - x0);
        uint8_t r = uint8_t(r_br + t * (r_bl - r_br));
        uint8_t g = uint8_t(g_br + t * (g_bl - g_br));
        uint8_t b = uint8_t(b_br + t * (b_bl - b_br));
        setPixel(x, y1, r, g, b);
    }

    // 左边
    for (uint32_t y = y1; y >= y0; y--)
    {
        float t = float(y1 - y) / float(y1 - y0);
        uint8_t r = uint8_t(r_bl + t * (r_tl - r_bl));
        uint8_t g = uint8_t(g_bl + t * (g_tl - g_bl));
        uint8_t b = uint8_t(b_bl + t * (b_tl - b_bl));
        setPixel(x0, y, r, g, b);
    }

    // B
    setPixel(3, 3, 30, 144, 207);
    setPixel(4, 3, 30, 144, 207);
    setPixel(5, 3, 30, 144, 207);

    setPixel(3, 4, 30, 144, 207);
    setPixel(6, 4, 30, 144, 207);

    setPixel(3, 5, 30, 144, 207);
    setPixel(6, 5, 30, 144, 207);

    setPixel(3, 6, 30, 144, 207);
    setPixel(4, 6, 30, 144, 207);
    setPixel(5, 6, 30, 144, 207);
    setPixel(3, 7, 30, 144, 207);
    setPixel(6, 7, 30, 144, 207);

    setPixel(3, 8, 30, 144, 207);
    setPixel(6, 8, 30, 144, 207);
    setPixel(3, 9, 30, 144, 207);
    setPixel(4, 9, 30, 144, 207);
    setPixel(5, 9, 30, 144, 207);

    // C
    setPixel(9, 3, 30, 144, 207);
    setPixel(10, 3, 30, 144, 207);

    setPixel(8, 4, 30, 144, 207);
    setPixel(11, 4, 30, 144, 207);
    setPixel(8, 5, 30, 144, 207);

    setPixel(8, 6, 30, 144, 207);

    setPixel(8, 7, 30, 144, 207);
    setPixel(8, 8, 30, 144, 207);
    setPixel(11, 8, 30, 144, 207);

    setPixel(9, 9, 30, 144, 207);
    setPixel(10, 9, 30, 144, 207);
    // S
    setPixel(14, 3, 30, 144, 207);
    setPixel(15, 3, 30, 144, 207);

    setPixel(13, 4, 30, 144, 207);
    setPixel(16, 4, 30, 144, 207);
    setPixel(13, 5, 30, 144, 207);

    setPixel(14, 6, 30, 144, 207);
    setPixel(15, 6, 30, 144, 207);

    setPixel(16, 7, 30, 144, 207);

    setPixel(13, 8, 30, 144, 207);
    setPixel(16, 8, 30, 144, 207);

    setPixel(14, 9, 30, 144, 207);
    setPixel(15, 9, 30, 144, 207);

    // 0
    setPixel(9 + 1, 11 + 4, 0, 0, 0);
    setPixel(10 + 1, 11 + 4, 0, 0, 0);

    setPixel(8 + 1, 12 + 4, 0, 0, 0);
    setPixel(11 + 1, 12 + 4, 0, 0, 0);

    setPixel(8 + 1, 13 + 4, 0, 0, 0);
    setPixel(10 + 1, 13 + 4, 0, 0, 0);
    setPixel(11 + 1, 13 + 4, 0, 0, 0);

    setPixel(8 + 1, 14 + 4, 0, 0, 0);
    setPixel(9 + 1, 14 + 4, 0, 0, 0);
    setPixel(11 + 1, 14 + 4, 0, 0, 0);

    setPixel(8 + 1, 15 + 4, 0, 0, 0);
    setPixel(11 + 1, 15 + 4, 0, 0, 0);

    setPixel(8 + 1, 16 + 4, 0, 0, 0);
    setPixel(11 + 1, 16 + 4, 0, 0, 0);

    setPixel(9 + 1, 17 + 4, 0, 0, 0);
    setPixel(10 + 1, 17 + 4, 0, 0, 0);

    // 0

    setPixel(14 + 1, 11 + 4, 0, 0, 0);
    setPixel(15 + 1, 11 + 4, 0, 0, 0);
    setPixel(13 + 1, 12 + 4, 0, 0, 0);
    setPixel(16 + 1, 12 + 4, 0, 0, 0);
    setPixel(13 + 1, 13 + 4, 0, 0, 0);
    setPixel(15 + 1, 13 + 4, 0, 0, 0);
    setPixel(16 + 1, 13 + 4, 0, 0, 0);
    setPixel(13 + 1, 14 + 4, 0, 0, 0);
    setPixel(14 + 1, 14 + 4, 0, 0, 0);
    setPixel(16 + 1, 14 + 4, 0, 0, 0);
    setPixel(13 + 1, 15 + 4, 0, 0, 0);
    setPixel(16 + 1, 15 + 4, 0, 0, 0);
    setPixel(13 + 1, 16 + 4, 0, 0, 0);
    setPixel(16 + 1, 16 + 4, 0, 0, 0);
    setPixel(14 + 1, 17 + 4, 0, 0, 0);
    setPixel(15 + 1, 17 + 4, 0, 0, 0);

    // 1
    setPixel(19 + 1, 11 + 4, 0, 0, 0);
    setPixel(18 + 1, 12 + 4, 0, 0, 0);
    setPixel(19 + 1, 12 + 4, 0, 0, 0);
    setPixel(19 + 1, 13 + 4, 0, 0, 0);
    setPixel(19 + 1, 14 + 4, 0, 0, 0);
    setPixel(19 + 1, 15 + 4, 0, 0, 0);
    setPixel(19 + 1, 16 + 4, 0, 0, 0);
    setPixel(18 + 1, 17 + 4, 0, 0, 0);
    setPixel(19 + 1, 17 + 4, 0, 0, 0);
    setPixel(20 + 1, 17 + 4, 0, 0, 0);
    image.setData(data);
    std::cout << "空心矩形渲染完成，保存为 test_image.ppm" << std::endl;
    return 0;
}

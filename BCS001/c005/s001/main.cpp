#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include "ppm.h"
#include "Vec2.h"

struct AABB
{
    lcg::Vec2 min;
    lcg::Vec2 max;
};

AABB computeAABB(const lcg::Vec2 &A, const lcg::Vec2 &B, const lcg::Vec2 &C)
{
    AABB box;
    box.min.x = std::min({A.x, B.x, C.x});
    box.min.y = std::min({A.y, B.y, C.y});
    box.max.x = std::max({A.x, B.x, C.x});
    box.max.y = std::max({A.y, B.y, C.y});
    return box;
}
static void setBufferPixel(std::vector<uint8_t> &data, uint32_t width, uint32_t height,
                           int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    if (x < 0 || y < 0 || x >= static_cast<int>(width) || y >= static_cast<int>(height))
    {
        return;
    }
    const size_t index = (static_cast<size_t>(y) * width + static_cast<size_t>(x)) * 3;
    data[index] = r;
    data[index + 1] = g;
    data[index + 2] = b;
}

void draw_triangle_with_ssaa(std::vector<uint8_t> &buffer, uint32_t width, uint32_t height,
                             lcg::Vec2 A, lcg::Vec2 B, lcg::Vec2 C, const int ssaa_factor = 4)
{
    AABB box = computeAABB(A, B, C);

    lcg::Vec2 AB = B - A;
    lcg::Vec2 BC = C - B;
    lcg::Vec2 CA = A - C;
    const int min_x = std::max(0, static_cast<int>(std::floor(box.min.x)));
    const int min_y = std::max(0, static_cast<int>(std::floor(box.min.y)));
    const int max_x = std::min(static_cast<int>(width) - 1, static_cast<int>(std::ceil(box.max.x)));
    const int max_y = std::min(static_cast<int>(height) - 1, static_cast<int>(std::ceil(box.max.y)));
    for (int y = min_y; y <= max_y; ++y)
    {
        for (int x = min_x; x <= max_x; ++x)
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

                uint8_t color = static_cast<uint8_t>(255.0f * coverage);
                setBufferPixel(buffer, width, height, x, y, color, color, color);
            }
        }
    }
}
int main()
{
    lcg::Vec2 A{100, 100};
    lcg::Vec2 B{200, 250};
    lcg::Vec2 C{300, 100};
    uint32_t width = 400;
    uint32_t height = 400;
    std::vector<uint8_t> buffer(static_cast<size_t>(width) * height * 3, 0);
    lcg::PPM ppm(".", "triangle", width, height);
    draw_triangle_with_ssaa(buffer, width, height, A, B, C, 16);
    ppm.setData(buffer);
    std::cout << "创建 triangle.ppm 成功" << std::endl;
    return 0;
}

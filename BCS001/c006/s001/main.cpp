#include <iostream>
#include <vector>
#include "ppm.h"
#include "Vec2.h"
#include "Rasterizer.h"

int main()
{
    uint32_t width = 400;
    uint32_t height = 400;
    lcg::PPM ppm(".", "triangle", width, height);
    std::vector<uint8_t> colorBuffer(width * height * 3, 0);

    lcg::Vec2 A0{100, 100};
    lcg::Vec2 B0{200, 250};
    lcg::Vec2 C0{300, 100};
    lcg::Color color0{255, 0, 0};
    lcg::draw_triangle_with_ssaa(colorBuffer, width, height, A0, B0, C0, color0, 16);

    lcg::Vec2 A1{100, 150};
    lcg::Vec2 B1{200, 300};
    lcg::Vec2 C1{300, 150};
    lcg::Color color1{0, 255, 0};
    lcg::draw_triangle_with_ssaa(colorBuffer, width, height, A1, B1, C1, color1, 16);

    lcg::Vec2 A2{150, 120};
    lcg::Vec2 B2{250, 270};
    lcg::Vec2 C2{350, 120};
    lcg::Color color2{0, 0, 255};
    lcg::draw_triangle_with_ssaa(colorBuffer, width, height, A2, B2, C2, color2, 16);

    ppm.setData(colorBuffer);
    std::cout << "创建 triangle.ppm 成功" << std::endl;
    return 0;
}

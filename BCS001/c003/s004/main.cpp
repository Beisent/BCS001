#include <algorithm>
#include <iostream>
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
void draw_triangle(lcg::PPM &ppm, lcg::Vec2 A, lcg::Vec2 B, lcg::Vec2 C)
{
    AABB box = computeAABB(A, B, C);

    lcg::Vec2 AB = B - A;
    lcg::Vec2 BC = C - B;
    lcg::Vec2 CA = A - C;
    for (int y = (int)box.min.y; y <= (int)box.max.y; ++y)
    {
        for (int x = (int)box.min.x; x <= (int)box.max.x; ++x)
        {
            lcg::Vec2 P(x + 0.5f, y + 0.5f);

            lcg::Vec2 AP = P - A;
            lcg::Vec2 BP = P - B;
            lcg::Vec2 CP = P - C;

            float cross1 = AB.cross(AP);
            float cross2 = BC.cross(BP);
            float cross3 = CA.cross(CP);

            if ((cross1 >= 0 && cross2 >= 0 && cross3 >= 0) ||
                (cross1 <= 0 && cross2 <= 0 && cross3 <= 0))
            {
                ppm.setPixel(x, y, lcg::Color(255, 255, 255));
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
    lcg::PPM ppm(".", "triangle", width, height);
    draw_triangle(ppm, A, B, C);
    std::cout << "创建 triangle.ppm 成功" << std::endl;
    return 0;
}

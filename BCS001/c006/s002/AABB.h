#pragma once
#include "Vec2.h"

namespace lcg
{
    struct AABB
    {
        lcg::Vec2 min;
        lcg::Vec2 max;
    };
    AABB computeAABB(const lcg::Vec3 &A, const lcg::Vec3 &B, const lcg::Vec3 &C)
    {
        AABB box;

        box.min.x = std::min({A.x, B.x, C.x});

        box.min.y = std::min({A.y, B.y, C.y});

        box.max.x = std::max({A.x, B.x, C.x});

        box.max.y = std::max({A.y, B.y, C.y});

        return box;
    }
}
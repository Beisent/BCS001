#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include "Vec3.h"
#include "AABB.h"
#include "Color.h"

namespace lcg
{

    struct EdgeData
    {
        float stepX, stepY;
        float initValue;
    };

    inline EdgeData prepare_edge(const Vec3 &v0, const Vec3 &v1, float minX, float minY)
    {
        EdgeData ed;
        ed.stepX = v0.y - v1.y;
        ed.stepY = v1.x - v0.x;
        ed.initValue = (minX - v0.x) * (v1.y - v0.y) - (minY - v0.y) * (v1.x - v0.x);
        return ed;
    }
    inline float edge_function(const lcg::Vec3 &A, const lcg::Vec3 &B, float x, float y)
    {
        return (x - A.x) * (B.y - A.y) - (y - A.y) * (B.x - A.x);
    }

    void draw_triangle(
        std::vector<uint8_t> &data,
        std::vector<float> &depthBuffer,
        uint32_t width, uint32_t height,
        Vec3 A, Vec3 B, Vec3 C,
        Color color)
    {
        if (width == 0 || height == 0)
        {
            return;
        }

        AABB box = computeAABB(A, B, C);
        int minX = std::max(0, (int)std::floor(box.min.x));
        int minY = std::max(0, (int)std::floor(box.min.y));
        int maxX = std::min((int)width - 1, (int)std::ceil(box.max.x));
        int maxY = std::min((int)height - 1, (int)std::ceil(box.max.y));

        float area = edge_function(A, B, C.x, C.y);
        if (std::abs(area) < 1e-6f)
            return;
        const float invArea = 1.0f / area;

        for (int y = minY; y <= maxY; ++y)
        {
            for (int x = minX; x <= maxX; ++x)
            {
                const float px = x + 0.5f;
                const float py = y + 0.5f;

                const float e0 = edge_function(A, B, px, py);
                const float e1 = edge_function(B, C, px, py);
                const float e2 = edge_function(C, A, px, py);

                if ((e0 >= 0 && e1 >= 0 && e2 >= 0) || (e0 <= 0 && e1 <= 0 && e2 <= 0))
                {
                    const float wA = e1 * invArea;
                    const float wB = e2 * invArea;
                    const float wC = e0 * invArea;
                    const float depth = wA * A.z + wB * B.z + wC * C.z;

                    const size_t pixel_idx = static_cast<size_t>(y) * width + x;
                    if (depth < depthBuffer[pixel_idx])
                    {
                        depthBuffer[pixel_idx] = depth;
                        const size_t img_idx = pixel_idx * 3;
                        data[img_idx + 0] = color.r;
                        data[img_idx + 1] = color.g;
                        data[img_idx + 2] = color.b;
                    }
                }
            }
        }
    }
}

#pragma once
#include <cmath>
namespace lcg
{
    struct Vec3
    {
        float x, y, z;
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
        Vec3() : x(0), y(0), z(0) {}

        Vec3 operator+(const Vec3 &other) const
        {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }
        Vec3 operator-(const Vec3 &other) const
        {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }
        Vec3 operator*(float scalar) const
        {
            return Vec3(x * scalar, y * scalar, z * scalar);
        }
        Vec3 operator/(float scalar) const
        {
            return Vec3(x / scalar, y / scalar, z / scalar);
        }
        float length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }
        Vec3 normalized() const
        {
            float len = length();
            if (len == 0)
                return Vec3(0, 0, 0);
            return Vec3(x / len, y / len, z / len);
        }
        float dot(const Vec3 &other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }
    };
    inline Vec3 operator*(float scalar, const Vec3 &v) { return v * scalar; }
}

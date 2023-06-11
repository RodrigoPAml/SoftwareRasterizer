#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer
{
    /// <summary>
    /// Represents a vector with 3 componentes
    /// </summary>
    template <typename T>
    class Vec3
    {
    public:
        T x;
        T y;
        T z;

        Vec3() : x(T()), y(T()), z(T()) {}

        Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

        Vec3(const Vec3<T>& other) : x(other.x), y(other.y), z(other.z) {}

        Vec3<T>& operator=(const Vec3<T>& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        Vec3<T> operator+(const Vec3<T>& other) const 
        {
            return Vec3<T>(x + other.x, y + other.y, z + other.z);
        }

        Vec3<T> operator-(const Vec3<T>& other) const
        {
            return Vec3<T>(x - other.x, y - other.y, z - other.z);
        }

        Vec3<T> operator*(T scalar) const 
        {
            return Vec3<T>(x * scalar, y * scalar, z * scalar);
        }

        Vec3<T> operator/(T scalar) const 
        {
            return Vec3<T>(x/scalar, y/scalar, z/scalar);
        }

        Vec3<T> operator+(T n) const
        {
            return Vec3<T>(x+n, y+n, z+n);
        }

        Vec3<T> operator*(const Vec3<T>& other) const 
        {
            return Vec3<T>(x * other.x, y * other.y, z * other.z);
        }

        Vec3<T> operator/(const Vec3<T>& other) const 
        {
            return Vec3<T>(x/other.x, y/other.y, z/other.z);
        }
    };
}

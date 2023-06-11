#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer
{
    /// <summary>
    /// Represents a vector with 3 componentes
    /// </summary>
    template <typename T>
    class Vec4
    {
    public:
        T x;
        T y;
        T z;
        T w;

        Vec4() : x(T()), y(T()), z(T()), w(T()) {}

        Vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

        Vec4(const Vec4<T>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

        Vec4<T>& operator=(const Vec4<T>& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;

            return *this;
        }

        Vec4<T> operator+(const Vec4<T>& other) const 
        {
            return Vec4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Vec4<T> operator-(const Vec4<T>& other) const
        {
            return Vec4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Vec4<T> operator*(T scalar) const 
        {
            return Vec4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        Vec4<T> operator/(T scalar) const 
        {
            return Vec4<T>(x/scalar, y/scalar, z/scalar, w/scalar);
        }

        Vec4<T> operator*(const Vec4<T>& other) const 
        {
            return Vec4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        Vec4<T> operator/(const Vec4<T>& other) const 
        {
            return Vec4<T>(x/other.x, y/other.y, z/other.z, w/other.w);
        }
    };
}

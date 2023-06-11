#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer
{
    /// <summary>
    /// Represents a vector with 2 componentes
    /// </summary>
    template <typename T>
    class Vec2
    {
    public:
        T x;
        T y;

        Vec2() : x(T()), y(T()) {}

        Vec2(T _x, T _y) : x(_x), y(_y) {}

        Vec2(const Vec2<T>& other) : x(other.x), y(other.y) {}

        Vec2<T>& operator=(const Vec2<T>& other)
        {
            x = other.x;
            y = other.y;

            return *this;
        }

        bool operator==(const Vec2<T>& other) const
        {
            return (x == other.x) && (y == other.y);
        }

        Vec2<T> operator+(const Vec2<T>& other) const 
        {
            return Vec2<T>(x + other.x, y + other.y);
        }

        Vec2<T> operator-(const Vec2<T>& other) const
        {
            return Vec2<T>(x - other.x, y - other.y);
        }

        Vec2<T> operator*(T scalar) const 
        {
            return Vec2<T>(x * scalar, y * scalar);
        }

        Vec2<T> operator/(T scalar) const 
        {
            return Vec2<T>(x/scalar, y/scalar);
        }

        Vec2<T> operator*(const Vec2<T>& other) const
        {
            return Vec2<T>(x * other.x, y * other.y);
        }

        Vec2<T> operator/(const Vec2<T>& other) const 
        {
            return Vec2<T>(x/other.x, y/other.y);
        }
    };
}

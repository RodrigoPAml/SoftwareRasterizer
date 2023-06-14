#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Importer {

    class Material
    {
        friend class Importer;
    private:
        Utils::Image image;

        Vec3<float> color;
    public:
        Material();
        ~Material();

        Vec3<float> GetTextureColor(const Vec2<float>& uv) const;
        Vec3<float> GetColor() const;
    };
}}

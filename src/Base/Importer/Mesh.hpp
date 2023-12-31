#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Importer {

    class Mesh
    {
        friend class Importer;
    private:
        float* vertices = nullptr;
        float* normals = nullptr;
        float* uvs = nullptr;

        int material = 0;

        int verticesSize = 0;

        Vec3<float> minBox, maxBox;
        bool haveNormals, haveUVs;
    public:
        ~Mesh();

        float* GetVertices() const;
        float* GetNormals() const;
        float* GetUVs() const;

        int GetVerticesSize() const;
        
        int GetMaterial() const;

        Vec3<float> GetMinBoundingBox() const;
        Vec3<float> GetMaxBoundingBox() const;

        bool HaveNormals() const;
    };
}}

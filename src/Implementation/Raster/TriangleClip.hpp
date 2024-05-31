#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Math {

    struct VertexData
    {
        Vec3<float> vertex;
        Vec3<float> normal;
        Vec2<float> uv;
    };

    /// <summary>
    /// Clipping de triangulos no eixo Z
    /// Foi chato de fazer e matou mais ainda a performance 
    /// mas sem ele em ambientes internos fica tudo bugado
    /// </summary>
    class TriangleClip 
    {
    public:
        static VertexData Clip
        (
            const VertexData& v1,
            const VertexData& v2,
            float min_z
        )
        {
            float t = (min_z - v1.vertex.z) / (v2.vertex.z - v1.vertex.z);
    
            Vec3<float> new_vertex(
                v1.vertex.x + t * (v2.vertex.x - v1.vertex.x),
                v1.vertex.y + t * (v2.vertex.y - v1.vertex.y),
                min_z
            );

            Vec3<float> new_normal(
                v1.normal.x + t * (v2.normal.x - v1.normal.x),
                v1.normal.y + t * (v2.normal.y - v1.normal.y),
                v1.normal.z + t * (v2.normal.z - v1.normal.z)
            );

            Vec2<float> new_uv(
                v1.uv.x + t * (v2.uv.x - v1.uv.x),
                v1.uv.y + t * (v2.uv.y - v1.uv.y)
            );

            return {
                new_vertex,
                new_normal,
                new_uv
            };
        }

        static std::vector<VertexData> ClipTriangle(
            const Vec3<float>& v1,
            const Vec3<float>& v2,
            const Vec3<float>& v3,
            const Vec3<float>& n1,
            const Vec3<float>& n2,
            const Vec3<float>& n3,
            const Vec2<float>& uv1,
            const Vec2<float>& uv2,
            const Vec2<float>& uv3,
            float minZ,
            bool clip
        ) 
        {
            std::vector<VertexData> vertices =
            {
                {v1, n1, uv1},
                {v2, n2, uv2},
                {v3, n3, uv3}
            };

            if (!clip)
                return vertices;

            std::vector<VertexData> inside, outside;
            for (const auto& vertexData : vertices) 
            {
                if (vertexData.vertex.z > minZ) 
                    inside.push_back(vertexData);
                else 
                    outside.push_back(vertexData);
            }

            if (inside.size() == 3)
            {
                return inside;
            }
            else if (inside.empty())
            {
                return {};
            }
            else if (inside.size() == 1)
            {
                return { inside[0], Clip(inside[0], outside[0], minZ), Clip(inside[0], outside[1], minZ) };
            }
            else if (inside.size() == 2) 
            {
                VertexData new_data1 =
                {
                    Clip(inside[0], outside[0], minZ),
                };

                VertexData new_data2 = 
                {
                    Clip(inside[1], outside[0], minZ),
                };

                return 
                {
                    inside[0], inside[1], new_data1,
                    inside[1], new_data1, new_data2
                };
            }

            return {};
        }
    };
}}
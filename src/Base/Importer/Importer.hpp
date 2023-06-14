#pragma once
#include <Rasterizer.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rasterizer {
namespace Importer
{
    class Importer
    {
    public:
        static ObjectPtr Load(const std::string& path);
    private:
        static void ProcessNode(aiNode* node, const aiScene* scene, ObjectPtr object);
        static void ProcessMesh(aiMesh* mesh, const aiScene* scene, ObjectPtr object);
        static void ProcessMaterials(const aiScene* scene, ObjectPtr object);
    };
}}
#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Importer {

    class Object
    {
        friend class Importer;
    private:
        std::string basePath;

        std::vector<Mesh> meshes;
        std::vector<Material> materials;
    public:
        std::vector<Mesh>& GetMeshes();
        std::vector<Material>& GetMaterials();
    };

    typedef std::shared_ptr<Object> ObjectPtr;
}}

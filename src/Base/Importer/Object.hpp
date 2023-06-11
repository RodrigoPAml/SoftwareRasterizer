#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Importer {

    class Object
    {
        friend class Importer;
    private:
        std::vector<Mesh> meshes;
    public:
        std::vector<Mesh>& GetMeshes();
    };

    typedef std::shared_ptr<Object> ObjectPtr;
}}

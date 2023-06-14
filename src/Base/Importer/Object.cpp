#include <Rasterizer.hpp>
#include "Object.hpp"

namespace Rasterizer {
namespace Importer {
	
	std::vector<Mesh>& Object::GetMeshes()
	{
		return this->meshes;
	}

	std::vector<Material>& Object::GetMaterials()
	{
		return this->materials;
	}
}}
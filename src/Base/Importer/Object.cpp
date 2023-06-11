#include <Rasterizer.hpp>
#include "Object.hpp"

namespace Rasterizer {
namespace Importer {
	
	std::vector<Mesh>& Object::GetMeshes()
	{
		return this->meshes;
	}
}}
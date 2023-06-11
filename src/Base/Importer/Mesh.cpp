#include <Rasterizer.hpp>
#include "Mesh.hpp"

namespace Rasterizer {
namespace Importer {

	float* Mesh::GetVertices() const
	{
		return this->vertices;
	}

	float* Mesh::GetNormals() const
	{
		return this->normals;
	}

	int Mesh::GetVerticesSize() const
	{
		return this->verticesSize;
	}

	int Mesh::GetMaterial() const
	{
		return this->material;
	}

	Vec3<float> Mesh::GetMinBoundingBox() const
	{
		return this->minBox;
	}

	Vec3<float> Mesh::GetMaxBoundingBox() const
	{
		return this->maxBox;
	}

	bool Mesh::HaveNormals() const
	{
		return this->haveNormals;
	}
}}
#include <Rasterizer.hpp>
#include "Mesh.hpp"

namespace Rasterizer {
namespace Importer {

	Mesh::~Mesh()
	{
		//if (this->vertices != nullptr)
		//	delete[] this->vertices;

		//if (this->normals != nullptr)
		//	delete[] this->normals;

		//if (this->uvs != nullptr)
		//	delete[] this->uvs;
	}

	float* Mesh::GetVertices() const
	{
		return this->vertices;
	}

	float* Mesh::GetNormals() const
	{
		return this->normals;
	}

	float* Mesh::GetUVs() const
	{
		return this->uvs;
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
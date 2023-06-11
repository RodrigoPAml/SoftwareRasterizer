#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace GPU {

	/// <summary>
	/// Describe an element that compose a vertex array.
	/// </summary>
	struct VertexElement
	{
		unsigned int count = 0;

		bool isNormalized = false;

		VertexElement() = default;

		VertexElement(const unsigned int count, const bool isNormalized = false)
		{
			this->count = count;
			this->isNormalized = isNormalized;
		}
	};

	/// <summary>
	/// Describes a buffer of vertices.
	/// </summary>
	struct VertexBufferDescriptor
	{
		std::vector<VertexElement> elements = std::vector<VertexElement>();

		void* data = nullptr;

		DataUse use = DataUse::STATIC_DRAW;

		VertexBufferType type = VertexBufferType::FLOAT;

		VertexBufferDescriptor() = default;

		VertexBufferDescriptor(const std::vector<VertexElement>& elements, void* data, const DataUse use, VertexBufferType type)
		{
			this->elements = elements;
			this->data = data;
			this->use = use;
			this->type = type;
		}
	};

	/// <summary>
	/// Describes a Vertex Array in GPU.
	/// </summary>
	struct VertexDescriptor
	{
		std::vector<VertexBufferDescriptor> buffers = std::vector<VertexBufferDescriptor>();

		unsigned int verticesCount = 0;

		VertexDescriptor() = default;

		VertexDescriptor(const std::vector<VertexBufferDescriptor>& buffers, const unsigned int verticesCount)
		{
			this->buffers = buffers;
			this->verticesCount = verticesCount;
		}
	};

	/// <summary>
	/// Describes a the indices of a Vertex Array.
	/// </summary>
	struct VertexIndicesDescriptor
	{
		unsigned int* indices = nullptr;

		unsigned int count = 0;

		DataUse use = DataUse::STATIC_DRAW;

		VertexIndicesDescriptor() = default;

		VertexIndicesDescriptor(unsigned int* indices, const unsigned int count, const DataUse use)
		{
			this->indices = indices;
			this->count = count;
			this->use = use;
		}
	};

	/// <summary>
	/// Get the size of each vertex data type in bytes.
	/// </summary>
	static unsigned int GetSizeOfVertexBufferType(const VertexBufferType type)
	{
		switch (type)
		{
		case VertexBufferType::BYTE:
			return 1;
		case VertexBufferType::UBYTE:
			return 1;
		case VertexBufferType::SHORT:
			return 2;
		case VertexBufferType::USHORT:
			return 2;
		case VertexBufferType::INT:
			return 4;
		case VertexBufferType::UINT:
			return 4;
		case VertexBufferType::HALF_FLOAT:
			return 2;
		case VertexBufferType::FLOAT:
			return 4;
		case VertexBufferType::DOUBLE:
			return 8;
		case VertexBufferType::INT_2_10_10_10_REV:
			return 4;
		case VertexBufferType::UINT_2_10_10_10_REV:
			return 4;
		default:
			return 0;
		}
	}
}}
#include <Rasterizer.hpp>
#include "Vertex.hpp"

namespace Rasterizer {
namespace GPU {

	int Vertex::TotalInstances = 0;

	Vertex::Vertex(const VertexDescriptor& descriptor)
	{
		Vertex::TotalInstances++;

		this->vao = 0;
		this->vaoSize = descriptor.verticesCount;

		this->ibo = 0;
		this->iboSize = 0;

		this->vbos = new unsigned int[descriptor.buffers.size()];
		this->vbosSize = descriptor.buffers.size();

		// First create an Vertex Array Object
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);

		// Then allocate the Vertex Buffers Objects
		glGenBuffers(descriptor.buffers.size(), this->vbos);

		// Now for each buffer we allocate the required memory.
		for(int i = 0; i < descriptor.buffers.size(); i++)
		{
			int elementsSize = 0;
			auto type = descriptor.buffers[i].type;

			for(const VertexElement& element : descriptor.buffers[i].elements)
			{
				// Elements size will be the all elements multiplied by the ocurrences ex: (3 * FLOAT_SIZE + 2 * FLOAT_SIZE)
				elementsSize += GetSizeOfVertexBufferType(type) * element.count;
			}

			// The buffer size is the elements size multiplied by how many elements are.
			int bufferSize = elementsSize * descriptor.verticesCount;
			glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);

			// Allocate memory for the buffer
			glBufferData(GL_ARRAY_BUFFER, bufferSize, descriptor.buffers[i].data, (GLenum)descriptor.buffers[i].use);
		}

		int index = 0;
		// Here we bind the elements layout into the buffers
		for(int i = 0; i < descriptor.buffers.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);

			int elementsSize = 0, currentOffset = 0;
			auto type = descriptor.buffers[i].type;

			for(const VertexElement& element : descriptor.buffers[i].elements)
			{
				elementsSize += GetSizeOfVertexBufferType(type) * element.count;
			}

			for(const VertexElement element : descriptor.buffers[i].elements)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.count, (GLenum)type, (GLboolean)element.isNormalized, elementsSize, (void*)currentOffset);
					
				currentOffset += element.count * GetSizeOfVertexBufferType(type);

				index++;
			}
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Vertex::Vertex(const VertexDescriptor& descriptor, const VertexIndicesDescriptor& indicesDescriptor) : Vertex(descriptor)
	{
		glBindVertexArray(this->vao);

		this->iboSize = indicesDescriptor.count;
		glGenBuffers(1, &this->ibo);

		unsigned int IndiceBufferSize = GetSizeOfVertexBufferType(VertexBufferType::UINT) * indicesDescriptor.count;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndiceBufferSize, indicesDescriptor.indices, (GLenum)indicesDescriptor.use);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Vertex::~Vertex()
	{
		Vertex::TotalInstances--;

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (this->vao != 0)
		{
			glDeleteVertexArrays(1, &this->vao);
			glDeleteBuffers(this->vbosSize, this->vbos);
		}

		if(this->ibo != 0)
			glDeleteBuffers(1, &this->ibo);

		if (this->vbos != nullptr)
		{
			delete[] this->vbos;
			this->vbos = nullptr;
		}
	}

	void Vertex::Use() const
	{
		glBindVertexArray(this->vao);
	}

	void Vertex::Draw(const DrawingType& drawingType) const
	{
		if(this->ibo != 0)
			glDrawElements((GLenum)drawingType, this->iboSize, (GLenum)VertexBufferType::UINT, 0);
		else 
			glDrawArrays((GLenum)drawingType, 0, this->vaoSize);
	}

	void Vertex::ModifyData(const unsigned int buffer, const unsigned int start, const unsigned int tam, void* data) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->vbos[buffer]);
		glBufferSubData(GL_ARRAY_BUFFER, start, tam, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vertex::ClearCurrentActive()
	{
		glBindVertexArray(0);
	}
	
	int Vertex::GetInstanceCount()
	{
		return Vertex::TotalInstances;
	}
}}
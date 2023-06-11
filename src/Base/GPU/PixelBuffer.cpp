#include "Rasterizer.hpp"
#include "PixelBuffer.hpp"

namespace Rasterizer {
namespace GPU {
	
	PixelBuffer::PixelBuffer(int width, int height, int size)
	{
		this->width = width;
		this->height = height;
		this->componentSize = size;

		glGenBuffers(1, &this->id);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, this->id);

		this->totalSize = width * height * size;

		glBufferData(GL_PIXEL_UNPACK_BUFFER, totalSize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
	PixelBuffer::~PixelBuffer()
	{
		if (this->id != 0)
		{
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
			glDeleteBuffers(1, &this->id);
		}
	}
	unsigned char* PixelBuffer::GetPixels()
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, this->id);

		return (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
	}

	void PixelBuffer::SavePixels(TexturePtr texture)
	{
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}

	int PixelBuffer::GetHeight() const
	{
		return this->height;
	}

	int PixelBuffer::GetWidth() const
	{
		return this->width;
	}

	int PixelBuffer::GetComponentSize() const
	{
		return this->componentSize;
	}

	int PixelBuffer::GetSize() const
	{
		return this->totalSize;
	}
}}


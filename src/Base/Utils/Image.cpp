#include <Rasterizer.hpp>
#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Rasterizer {
namespace Utils {

	Image::Image(const std::string& path, bool flipVertically)
	{
		stbi_set_flip_vertically_on_load(flipVertically);

		int numComponents = 0;
		this->data = stbi_load(path.c_str(), &this->size.x, &this->size.y, &numComponents, 0);
		this->path = path;

		if (!this->data)
			throw std::exception(("Failed to open texture in path: " + path).c_str());

		if (this->size.x <= 0 || this->size.y <= 0)
		{
			if (this->data != nullptr)
				delete[] this->data;
		}

		switch (numComponents)
		{
			case 1:
				this->format = GPU::TextureFormat::R;
				break;
			case 3:
				this->format = GPU::TextureFormat::RGB;
				break;
			case 4:
				this->format = GPU::TextureFormat::RGBA;
				break;
			default:
				if (this->data != nullptr)
					delete[] this->data;
		}
	}

	Image::~Image()
	{
		//if (this->data != nullptr)
		//	delete[] this->data;
	}

	void Image::SetSize(const Vec2<int>& size)
	{
		this->size = size;
	}

	void Image::SetData(unsigned char* data)
	{
		this->data = data;
	}

	void Image::SetFormat(const  GPU::TextureFormat& format)
	{
		this->format = format;
	}

	Vec2<int> Image::GetSize() const
	{
		return this->size;
	}

	unsigned char* Image::GetData() const
	{
		return this->data;
	}

	GPU::TextureFormat Image::GetFormat() const
	{
		return this->format;
	}

	std::string Image::GetLoadedPath() const
	{
		return this->path;
	}
}}
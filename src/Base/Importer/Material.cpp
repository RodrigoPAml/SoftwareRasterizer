#include <Rasterizer.hpp>
#include "Material.hpp"

namespace Rasterizer {
namespace Importer {
	
	Material::Material()
	{
	}

	Material::~Material()
	{
		//if (this->texture != nullptr)
		//	delete[] this->texture;
	}

	Vec3<float> Material::GetTextureColor(const Vec2<float>& uv) const
	{
		Vec3<float> color = { 1.0f, 0 , 0.0f };

		auto img = image.GetData();

		if (img == nullptr)
			return GetColor();

		int textureWidth = this->image.GetSize().x;
		int textureHeight = this->image.GetSize().y;

		int x = (int)(std::abs(uv.x) * textureWidth) % textureWidth;
		int y = (int)(std::abs(uv.y) * textureHeight) % textureHeight;

		int texelSize = this->image.GetFormat() == GPU::TextureFormat::RGB ? 3 : 4;
		int index = y * textureWidth * texelSize + x * texelSize;

		if (index > 0 && index+2 < textureWidth * texelSize * textureHeight)
			return { (float)(img[index] / 255.0f), (float)(img[index+1] / 255.0f) , (float)(img[index+2] / 255.0f) };
		else 
			return color;
	}

	Vec3<float> Material::GetColor() const
	{
		return this->color;
	}
}}
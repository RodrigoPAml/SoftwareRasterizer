#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace GPU {

	/// <summary>
	/// Configuration so send a texture in memory to CPU.
	/// </summary>
	struct TextureDataConfiguration
	{
		MinifyingFilter minifyingFilter = MinifyingFilter::LINEAR_MIPMAP_LINEAR;
		MagnificationFilter magnificationFilter = MagnificationFilter::LINEAR;

		TextureWrap textureWrapT = TextureWrap::CLAMP_TO_EDGE;
		TextureWrap textureWrapS = TextureWrap::CLAMP_TO_EDGE;

		TextureInternalFormat internalFormat = TextureInternalFormat::RGB;
		TexturePixelFormat pixelFormat = TexturePixelFormat::FLOAT;

		Vec3<float> borderColor = { 0, 0, 0 };
		unsigned int ansiotropicFilter = 2;
	};

	/// <summary>
	/// Configuration to create an empty texture in CPU.
	/// </summary>
	struct TextureConfiguration : TextureDataConfiguration
	{
		TextureFormat format = TextureFormat::RGB;

		Vec2<int> size = { 0,0 };
	};
}}
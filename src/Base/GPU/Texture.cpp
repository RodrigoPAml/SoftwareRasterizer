#include <Rasterizer.hpp>
#include "Texture.hpp"

namespace Rasterizer {
namespace GPU {

	int Texture::TotalInstances = 0;

	Texture::Texture(const TextureDataConfiguration& configuration, Utils::ImagePtr image)
	{
		Texture::TotalInstances++;

		this->id = 0;
		this->size = image->GetSize();
		this->format = image->GetFormat();

		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)configuration.textureWrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)configuration.textureWrapT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)configuration.minifyingFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)configuration.magnificationFilter);

		if(configuration.textureWrapS == TextureWrap::CLAMP_TO_BORDER || configuration.textureWrapT == TextureWrap::CLAMP_TO_EDGE)
		{
			float color[] = { configuration.borderColor.x, configuration.borderColor.y, configuration.borderColor.z, 1.0f};
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		}

		if(configuration.ansiotropicFilter > 0 && glfwExtensionSupported("GL_ARB_texture_filter_anisotropic"))
		{
			float largest_supported_anisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
				
			unsigned int supported = std::min((unsigned int)largest_supported_anisotropy, configuration.ansiotropicFilter);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, supported);
		}

		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			(GLint)configuration.internalFormat,
			image->GetSize().x,
			image->GetSize().y,
			0, 
			(GLint)image->GetFormat(),
			(GLenum)configuration.pixelFormat,
			image->GetData()
		);

		if(configuration.minifyingFilter != MinifyingFilter::ONLY_LINEAR && configuration.minifyingFilter != MinifyingFilter::ONLY_NEAREST)
			glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::Texture(const TextureConfiguration& configuration)
	{
		Texture::TotalInstances++;

		this->id = 0;
		this->size = configuration.size;
		this->format = configuration.format;

		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)configuration.textureWrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)configuration.textureWrapT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)configuration.minifyingFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)configuration.magnificationFilter);

		if (configuration.textureWrapS == TextureWrap::CLAMP_TO_BORDER || configuration.textureWrapT == TextureWrap::CLAMP_TO_EDGE)
		{
			float color[] = { configuration.borderColor.x, configuration.borderColor.y, configuration.borderColor.z, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		}

		if (configuration.ansiotropicFilter > 0 && glfwExtensionSupported("GL_ARB_texture_filter_anisotropic"))
		{
			float largest_supported_anisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);

			unsigned int supported = std::min((unsigned int)largest_supported_anisotropy, configuration.ansiotropicFilter);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, supported);
		}

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			(GLint)configuration.internalFormat,
			this->size.x,
			this->size.y,
			0,
			(GLint)this->format,
			(GLenum)configuration.pixelFormat,
			nullptr
		);

		if (configuration.minifyingFilter != MinifyingFilter::ONLY_LINEAR && configuration.minifyingFilter != MinifyingFilter::ONLY_NEAREST)
			glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::~Texture()
	{
		Texture::TotalInstances--;

		if (this->id != 0)
			glDeleteTextures(1, &this->id);
	}

	unsigned int Texture::GetId() const
	{
		return this->id;
	}

	void Texture::Use(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, this->id);
	}

	void Texture::DisableTextureUnit(const unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glDisable(GL_TEXTURE_2D);
	}

	unsigned int Texture::GetMaxTextureUnits()
	{
		int max = 0;

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max);

		return (unsigned int)max;
	}
	
	int Texture::GetInstanceCount()
	{
		return Texture::TotalInstances;
	}
}}
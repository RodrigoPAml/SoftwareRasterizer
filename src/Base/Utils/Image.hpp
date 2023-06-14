#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Utils {

	/// <summary>
	/// Represents a image in CPU memory.
	/// </summary>
	class Image
	{
	private:
		unsigned char* data;

		Vec2<int> size;

		GPU::TextureFormat format;

		std::string path;
	public:
		Image() {};
		Image(const std::string& path, bool flipVertically = false);
		~Image();

		void SetSize(const Vec2<int>& size);
		void SetData(unsigned char* data);
		void SetFormat(const GPU::TextureFormat& format);

		Vec2<int> GetSize() const;
		unsigned char* GetData() const;
		GPU::TextureFormat GetFormat() const;
		std::string GetLoadedPath() const;
	};

	typedef std::shared_ptr<Image> ImagePtr;
}}
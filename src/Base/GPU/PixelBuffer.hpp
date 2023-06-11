#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace GPU {

	/// <summary>
	/// Pixel buffer mapped directly from GPU
	/// </summary>
	class PixelBuffer
	{
	private:
		/// <summary>
		/// Identifier
		/// </summary>
		unsigned int id = 0;

		/// <summary>
		/// Buffer width
		/// </summary>
		int width;
			
		/// <summary>
		/// Buffer height
		/// </summary>
		int height;
	
		/// <summary>
		/// Buffer pixel size
		/// </summary>
		int componentSize;

		/// <summary>
		/// Total buffer size
		/// </summary>
		int totalSize;
	public:
		PixelBuffer(int width, int height, int size);
		~PixelBuffer();

		/// <summary>
		/// Get pixels to write
		/// </summary>
		unsigned char* GetPixels();

		/// <summary>
		/// Save pixels into texture of GPU
		/// </summary>
		void SavePixels(TexturePtr texture);

		// Gets
		int GetHeight() const;
		int GetWidth() const;
		int GetComponentSize() const;
		int GetSize() const;
	};

	typedef std::shared_ptr<PixelBuffer> PixelBufferPtr;
}}
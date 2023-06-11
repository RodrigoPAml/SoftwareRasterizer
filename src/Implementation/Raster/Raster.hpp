#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer
{
	class Raster
	{
	private:
		// Pixel Buffer shared with gpu for fast transfer pixels
		GPU::PixelBufferPtr buffer;

		// The texture to draw pixels
		GPU::TexturePtr texture;

		// Camera manager
		Camera camera;

		// Pointer to GPU pixels array
		unsigned char* pixels = nullptr;

		// Depth buffer
		float* depth = nullptr;

		// Cache for screen size and pixel size
		Vec2<float> pixelSize;
		Vec2<float> screenSize;
	public:
		Raster(int width, int height);

		void BeginDraw();
		void EndDraw();

		void DrawPixel(const Vec2<int>& pos, const Vec3<int>& color);

		void DrawLine(Vec2<int> pos1, Vec2<int> pos2, Vec3<int> color);
		
		void DrawWiredTriangle(const Vec2<float>& p0, const Vec2<float>& p1, const Vec2<float>& p2, const Vec3<int>& color);
		
		void DrawTriangle(
			const Vec3<float>& p0,
			const Vec3<float>& p1,
			const Vec3<float>& p2,
			const Vec3<float>& c1,
			const Vec3<float>& c2,
			const Vec3<float>& c3,
			const Vec3<float>& color
		);

		void DrawObject(Importer::ObjectPtr obj);
	
		bool CheckDepth(const Vec2<int>& pos, float z);
	};
}


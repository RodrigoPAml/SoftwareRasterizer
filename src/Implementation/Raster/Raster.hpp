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

		float speedCamera = 3.0f;
		float speedRotate = 150.0f;

		int drawMode = 0;

		int frameCount = 0;
		float fps = 0.0;
		float startTime = 0;
		float pattern = 1;

		bool backCulling = true;
		bool clip = true;

		Vec3<float> lightDir = { -1, 0, 0 };
		float ambientStr = 0.1;
		DrawMode mode = DrawMode::Textured;
		float lastTime = Utils::Time::GetTimestamp();
	public:
		Raster(Vec2<float> size);

		void BeginDraw();
		void EndDraw();

		void DrawPixel(const Vec2<int>& pos, const Vec3<int>& color);

		void DrawLine(Vec2<int> pos1, Vec2<int> pos2, Vec3<int> color);
		
		void DrawWiredTriangle(const Vec2<float>& p0, const Vec2<float>& p1, const Vec2<float>& p2, const Vec3<int>& color);
		
		void DrawTriangle(
			const Vec3<float>& p0,
			const Vec3<float>& p1,
			const Vec3<float>& p2,
			const Vec3<float>& n1,
			const Vec3<float>& n2,
			const Vec3<float>& n3,
			const Vec3<float>& w1,
			const Vec3<float>& w2,
			const Vec3<float>& w3,
			const Vec2<float>& uv1,
			const Vec2<float>& uv2,
			const Vec2<float>& uv3,
			const Importer::Material& mat
		);

		void DrawObject(Importer::ObjectPtr obj);
		bool CheckDepth(const Vec2<int>& pos, float z);
	};
}


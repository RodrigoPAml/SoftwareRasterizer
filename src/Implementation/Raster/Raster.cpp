 #include <Rasterizer.hpp>
#include "Raster.hpp"

namespace Rasterizer
{
	Raster::Raster(int width, int height)
	{
		this->pixelSize = { (float)width, (float)height };

		using namespace GPU;

		// Initilize Texture
		TextureConfiguration config;

		config.ansiotropicFilter = 0;
		config.format = TextureFormat::RGB;
		config.internalFormat = TextureInternalFormat::RGB;
		config.pixelFormat = TexturePixelFormat::UNSIGNED_INT;
		config.magnificationFilter = MagnificationFilter::NEAREST;
		config.minifyingFilter = MinifyingFilter::ONLY_NEAREST;
		config.size = { width, height };

		this->texture = GPU::TexturePtr(new GPU::Texture(config));

		// Create a pixel buffer between the GPU and CPU to fast pixel transfer
		this->buffer = PixelBufferPtr(new PixelBuffer(width, height, 3));
		this->depth = new float[width * height];
	}

	void Raster::BeginDraw()
	{
		using namespace GPU;
		using namespace Input;

		using Window = Window::Window;
		this->screenSize = Window::GetSize();

		Command::SwitchViewPort({ 0, 0 }, Math::Cast(this->screenSize));

		pixels = this->buffer->GetPixels();

		// Clear the pixels
		for (int i = 0; i < this->buffer->GetSize(); i++)
			pixels[i] = 0;

		// Clear the depth buffer
		for (int i = 0; i < this->pixelSize.x * this->pixelSize.y; i++)
			this->depth[i] = INT_MAX;

		// Translate camera
		if (Keyboard::GetKeyState(KeyboardKey::KEY_UP) >= InputAction::PRESS)
			this->camera.TranslateFront(1.1);
		if (Keyboard::GetKeyState(KeyboardKey::KEY_DOWN) >= InputAction::PRESS)
			this->camera.TranslateFront(-1.1);
		if (Keyboard::GetKeyState(KeyboardKey::KEY_LEFT) >= InputAction::PRESS)
			this->camera.TranslateRight(-1.1);
		if (Keyboard::GetKeyState(KeyboardKey::KEY_RIGHT) >= InputAction::PRESS)
			this->camera.TranslateRight(1.1);

		// Look camera around
		auto var = Mouse::GetMouseVariation();
		bool isClicked = Mouse::GetMouseButtonState(MouseButton::MOUSE_BUTTON_RIGHT) == InputAction::PRESS;

		if(var.y > 0 && isClicked)
			this->camera.SetPitch(this->camera.GetPitch() - 15);
		else if(var.y < 0 && isClicked)
			this->camera.SetPitch(this->camera.GetPitch() + 15);
		if (var.x > 0 && isClicked)
			this->camera.SetYaw(this->camera.GetYaw() + 15);
		else if (var.x < 0 && isClicked)
			this->camera.SetYaw(this->camera.GetYaw() - 15);
	}

	void Raster::EndDraw()
	{
		using namespace Drawing;

		// Send pixels to GPU then draw it
		this->buffer->SavePixels(this->texture);
		TextureRenderer::Draw(this->texture);
	}

	void Raster::DrawPixel(const Vec2<int>& pos, const Vec3<int>& color)
	{
		int lineWidth = this->pixelSize.x * this->buffer->GetComponentSize();

		int index = ((pos.y * lineWidth) + (pos.x * this->buffer->GetComponentSize()));

		if (pos.x < 0 || pos.y < 0 || pos.x >= this->pixelSize.x || pos.y >= this->pixelSize.y)
			return;

		pixels[index] = color.x;
		pixels[index + 1] = color.y;
		pixels[index + 2] = color.z;
	}

	void Raster::DrawLine(Vec2<int> pos1, Vec2<int> pos2, Vec3<int> color)
	{
		int dx = abs(pos2.x - pos1.x);
		int dy = abs(pos2.y - pos1.y);

		int sx = (pos1.x < pos2.x) ? 1 : -1;
		int sy = (pos1.y < pos2.y) ? 1 : -1;
		int err = dx - dy;

		while (true)
		{
			DrawPixel({ pos1.x, pos1.y }, color);

			if (pos1.x == pos2.x && pos1.y == pos2.y)
				break;

			int e2 = 2 * err;
			if (e2 > -dy) {
				err -= dy;
				pos1.x += sx;
			}
			if (e2 < dx) {
				err += dx;
				pos1.y += sy;
			}
		}
	}

	void Raster::DrawWiredTriangle(const Vec2<float>& p0, const Vec2<float>& p1, const Vec2<float>& p2, const Vec3<int>& color)
	{
		this->DrawLine(Math::Cast(p0), Math::Cast(p1), color);
		this->DrawLine(Math::Cast(p1), Math::Cast(p2), color);
		this->DrawLine(Math::Cast(p0), Math::Cast(p2), color);
	}

	void Raster::DrawTriangle(
		const Vec3<float>& p0, 
		const Vec3<float>& p1, 
		const Vec3<float>& p2, 
		const Vec3<float>& c1,
		const Vec3<float>& c2,
		const Vec3<float>& c3,
		const Vec3<float>& color
	)
	{
		std::vector<Vec3<float>> sortedVertices = { p0, p1, p2 };

		std::sort(sortedVertices.begin(), sortedVertices.end(), [](const Vec3<float>& a, const Vec3<float>& b) {
			return a.y < b.y;
		});

		const auto& top = sortedVertices[0];
		const auto& mid = sortedVertices[1];
		const auto& bot = sortedVertices[2];

		float invSlope1 = (mid.x - top.x) / (mid.y - top.y);
		float invSlope2 = (bot.x - top.x) / (bot.y - top.y);

		float curx1 = top.x;
		float curx2 = top.x;

		int maxWidth = std::min(std::max(p2.x, std::max(p0.x, p1.x)), this->pixelSize.x);
		int minWidth = std::max(std::min(p2.x, std::min(p0.x, p1.x)), 0.0f);

		float d = Math::Edge(p0, p1, p2);
		
		Vec3<float> inverseZ = { 1 / p0.z, 1 / p1.z, 1 / p2.z };

		Vec3<float> att1 = c1 / p0.z;
		Vec3<float> att2 = c2 / p1.z;
		Vec3<float> att3 = c3 / p2.z;

		for (int y = top.y; y <= mid.y; ++y)
		{
			int startX = curx1;
			int endX = curx2;

			if (startX > endX)
				std::swap(startX, endX);

			startX = std::max(startX, minWidth);
			startX = std::min(startX, maxWidth);

			endX = std::max(endX, minWidth);
			endX = std::min(endX, maxWidth);

			for (int pixelX = startX; pixelX <= endX; ++pixelX)
			{
				Vec2<int> p = { pixelX, y };

				Vec3<float> w = Pipeline::GetWeights(p0, p1, p2, p) / d;
				float z = 1 / (w.x * inverseZ.x + w.y * inverseZ.y + w.z * inverseZ.z);

				if (this->CheckDepth(p, z))
				{
					Vec3<float> att = Math::Normalize(Pipeline::InterpolateAttribute(att1, att2, att3, w) * z);

					float diff = (Math::Dot(att, { -1, 0, 0 }) + 1)/2;
					Vec3<float> lightColor = color * diff;

					DrawPixel(p, Math::Cast(lightColor*255));
				}
			}

			curx1 += invSlope1;
			curx2 += invSlope2;
		}

		invSlope1 = (bot.x - mid.x) / (bot.y - mid.y);
		curx1 = mid.x;

		for (int y = mid.y + 1; y <= bot.y; ++y)
		{
			int startX = curx1;
			int endX = curx2;

			if (startX > endX)
				std::swap(startX, endX);

			startX = std::max(startX, minWidth);
			startX = std::min(startX, maxWidth);

			endX = std::max(endX, minWidth);
			endX = std::min(endX, maxWidth);

			for (int pixelX = startX; pixelX <= endX; ++pixelX)
			{
				Vec2<int> p = { pixelX, y };

				Vec3<float> w = Pipeline::GetWeights(p0, p1, p2, p) / d;
				float z = 1 / (w.x * inverseZ.x + w.y * inverseZ.y + w.z * inverseZ.z);

				if (this->CheckDepth(p, z))
				{
					Vec3<float> att = Math::Normalize(Pipeline::InterpolateAttribute(att1, att2, att3, w) * z);

					float diff = (Math::Dot(att, { -1, 0, 0 }) + 1) / 2;
					Vec3<float> lightColor = color * diff;
					DrawPixel(p, Math::Cast(lightColor * 255));
				}
			}

			curx1 += invSlope1;
			curx2 += invSlope2;
		}
	}

	void Raster::DrawObject(Importer::ObjectPtr obj)
	{
		using namespace Importer;
		
		float zNear = this->camera.GetZNear();
		float zFar = this->camera.GetZFar();
		float fov = 1.0f / std::tan(this->camera.GetFov() / 2.0f);
		float aspectRatio = this->camera.GetAspectRatio();

		for (const Mesh& mesh : obj->GetMeshes())
		{
			auto vertices = mesh.GetVertices();
			auto colors = mesh.GetNormals();

			for (int i = 0; i < mesh.GetVerticesSize(); i += 9)
			{
				// World space
				Vec3<float> t1 = { vertices[i], vertices[i + 1], vertices[i + 2] };
				Vec3<float> t2 = { vertices[i + 3], vertices[i + 4], vertices[i + 5] };
				Vec3<float> t3 = { vertices[i + 6], vertices[i + 7], vertices[i + 8] };

				Vec3<float> n1 = { colors[i], colors[i + 1], colors[i + 2] };
				Vec3<float> n2 = { colors[i + 3], colors[i + 4], colors[i + 5] };
				Vec3<float> n3 = { colors[i + 6], colors[i + 7], colors[i + 8] };

				// Camera or View Space
				this->camera.ApplyToVertex(t1);
				this->camera.ApplyToVertex(t2);
				this->camera.ApplyToVertex(t3);

				// Project into the plane
				Pipeline::Project(t1, fov, aspectRatio);
				Pipeline::Project(t2, fov, aspectRatio);
				Pipeline::Project(t3, fov, aspectRatio);

				// Check if z component is inside znear and zfar range
				if (Pipeline::IsOutsidePlanes(t1, zNear, zFar) ||
					Pipeline::IsOutsidePlanes(t2, zNear, zFar) ||
					Pipeline::IsOutsidePlanes(t3, zNear, zFar))
					continue;
			
				// Normalize into screen space
				Pipeline::ScreenSpace(t1, this->pixelSize);
				Pipeline::ScreenSpace(t2, this->pixelSize);
				Pipeline::ScreenSpace(t3, this->pixelSize);

				DrawTriangle(t1, t2, t3, n1, n2, n3, {1.0f, 0.0f, 0.0f});
			}
		}
	}

	bool Raster::CheckDepth(const Vec2<int>& pos, float z)
	{
		int zIndex = (pos.y * this->pixelSize.x) + pos.x;

		if (zIndex < 0 || zIndex > this->pixelSize.x * this->pixelSize.y)
			return false;

		float currentZ = this->depth[zIndex];

		if (currentZ > z)
		{
			this->depth[zIndex] = z;
			return true;
		}

		return false;
	}
}
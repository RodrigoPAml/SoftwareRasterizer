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

		this->startTime = Utils::Time::GetTimestamp();
	}

	void Raster::BeginDraw()
	{
		using namespace GPU;
		using namespace Input;

		using GUI = Window::GUI;
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
			this->camera.TranslateFront(this->speedCamera);
		if (Keyboard::GetKeyState(KeyboardKey::KEY_DOWN) >= InputAction::PRESS)
			this->camera.TranslateFront(-this->speedCamera);
		if (Keyboard::GetKeyState(KeyboardKey::KEY_LEFT) >= InputAction::PRESS)
			this->camera.TranslateRight(-this->speedCamera);
		if (Keyboard::GetKeyState(KeyboardKey::KEY_RIGHT) >= InputAction::PRESS)
			this->camera.TranslateRight(this->speedCamera);

		// Look camera around
		auto var = Mouse::GetMouseVariation();
		bool isClicked = Mouse::GetMouseButtonState(MouseButton::MOUSE_BUTTON_RIGHT) >= InputAction::PRESS;

		if(var.y > 0 && isClicked)
			this->camera.SetPitch(this->camera.GetPitch() - this->speedRotate);
		else if(var.y < 0 && isClicked)
			this->camera.SetPitch(this->camera.GetPitch() + this->speedRotate);
		if (var.x > 0 && isClicked)
			this->camera.SetYaw(this->camera.GetYaw() + this->speedRotate);
		else if (var.x < 0 && isClicked)
			this->camera.SetYaw(this->camera.GetYaw() - this->speedRotate);
	}

	void Raster::EndDraw()
	{
		auto currentTime = Utils::Time::GetTimestamp();
		auto elapsedTime = (currentTime - this->startTime);

		this->frameCount++;;
		if (elapsedTime >= 1.0) 
		{
			this->fps = this->frameCount / elapsedTime;

			this->frameCount = 0;
			this->startTime = currentTime;
		}

		using namespace Drawing;
		using namespace GPU;

		using GUI = Window::GUI;

		// Send pixels to GPU then draw it
		this->buffer->SavePixels(this->texture);
		TextureRenderer::Draw(this->texture);

		GUI::BeginFrame();
		if (GUI::BeginWindow("Menu"))
		{
			GUI::Text("Resolution: ");
			GUI::ContinueSameLine();
			if (GUI::Input("pixelBufferSize", this->pixelSize))
			{
				// Initilize Texture
				TextureConfiguration config;

				config.ansiotropicFilter = 0;
				config.format = TextureFormat::RGB;
				config.internalFormat = TextureInternalFormat::RGB;
				config.pixelFormat = TexturePixelFormat::UNSIGNED_INT;
				config.magnificationFilter = MagnificationFilter::NEAREST;
				config.minifyingFilter = MinifyingFilter::ONLY_NEAREST;
				config.size = { (int)this->pixelSize.x, (int)this->pixelSize.y };

				this->texture = GPU::TexturePtr(new GPU::Texture(config));

				// Create a pixel buffer between the GPU and CPU to fast pixel transfer
				this->buffer = PixelBufferPtr(new PixelBuffer(this->pixelSize.x, this->pixelSize.y, 3));
				this->depth = new float[this->pixelSize.x * this->pixelSize.y];
			}

			GUI::Text("Mode: ");
			int mode = (int)this->mode;
			if (GUI::ComboBox("mode", { "Wireframe", "Light", "Normals", "World Position", "UVs", "Pattern", "Depth"}, mode))
				this->mode = (DrawMode)mode;

			GUI::Text("CameraSpeed: ");
			GUI::ContinueSameLine();
			GUI::Input("cameraSpeed", this->speedCamera);

			GUI::Text("Camera Rotation Speed: ");
			GUI::ContinueSameLine();
			GUI::Input("cameraRootSpeed", this->speedRotate);

			float fov = this->camera.GetFov();
			GUI::Text("Fov: ");
			GUI::ContinueSameLine();
			if (GUI::Input("fov", fov))
				this->camera.SetFov(fov);

			float asp = this->camera.GetAspectRatio();
			GUI::Text("Aspect Ratio: ");
			GUI::ContinueSameLine();
			if (GUI::Input("asp", asp))
				this->camera.SetAspectRatio(asp);

			GUI::Text("FPS: ");
			GUI::ContinueSameLine();
			GUI::Text(std::to_string(this->fps));

			GUI::Text("Patern: ");
			GUI::ContinueSameLine();
			GUI::Input("patern", this->pattern);

			float zfar = this->camera.GetZFar();
			GUI::Text("ZFar: ");
			GUI::ContinueSameLine();
			if (GUI::Input("zFar", zfar))
				this->camera.SetZFar(zfar);

			float znear = this->camera.GetZNear();
			GUI::Text("ZNear: ");
			GUI::ContinueSameLine();
			if (GUI::Input("zNear", znear))
				this->camera.SetZNear(znear);

		}
		GUI::EndFrame();
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
		const Vec3<float>& n1,
		const Vec3<float>& n2,
		const Vec3<float>& n3,
		const Vec3<float>& w1,
		const Vec3<float>& w2,
		const Vec3<float>& w3,
		const Vec3<float>& color
	)
	{
		int maxX = std::min(this->pixelSize.x, std::max(p2.x, std::max(p0.x, p1.x)));
		int minX = std::max(0.0f, std::min(p2.x, std::min(p0.x, p1.x)));

		int maxY = std::min(this->pixelSize.y, std::max(p2.y, std::max(p0.y, p1.y)));
		int minY = std::max(0.0f, std::min(p2.y, std::min(p0.y, p1.y)));

		float d = Math::Edge(p0, p1, p2);
		
		Vec3<float> inverseZ = { 1 / p0.z, 1 / p1.z, 1 / p2.z };

		Vec3<float> normal1 = n1 / p0.z;
		Vec3<float> normal2 = n2 / p1.z;
		Vec3<float> normal3 = n3 / p2.z;

		Vec3<float> pos1 = w1 / p0.z;
		Vec3<float> pos2 = w2 / p1.z;
		Vec3<float> pos3 = w3 / p2.z;

		Vec2<float> uv1 = { 0, 0 };
		Vec2<float> uv2 = { 1, 0 };
		Vec2<float> uv3 = { 0, 1 };

		uv1 = uv1 / p0.z;
		uv2 = uv2 / p1.z;
		uv3 = uv3 / p2.z;

		for (int y = minY; y <= maxY; ++y)
		{
			for (int x = minX; x <= maxX; ++x)
			{
				Vec2<int> p = {x , y};
				Vec3<float> w = Pipeline::GetWeights(p0, p1, p2, p);
				
				w = w / d;

				if (w.x >= 0 && w.y >= 0 && w.z >= 0) 
				{
					float z = 1 / (w.x * inverseZ.x + w.y * inverseZ.y + w.z * inverseZ.z);

					if (this->CheckDepth(p, z))
					{
						switch (mode)
						{
						case DrawMode::Colored:
							{
								Vec3<float> normal = Math::Normalize(Pipeline::InterpolateAttribute(normal1, normal2, normal3, w) * z);

								float diff = (Math::Dot(normal, { -1, 0, 0 }) + 1) / 2;
								Vec3<float> lightColor = (color * diff) + (color * 0.1);

								Math::Clamp(lightColor, 1.0f);

								DrawPixel(p, Math::Cast(lightColor * 255));
							}
							break;
						case DrawMode::Normals:
							{
								Vec3<float> normal = Math::Normalize(Pipeline::InterpolateAttribute(normal1, normal2, normal3, w) * z);
								DrawPixel(p, Math::Cast(normal * 255));
							}
							break;
						case DrawMode::Positions:
							{
								Vec3<float> pos = Pipeline::InterpolateAttribute(pos1, pos2, pos3, w) * z;
								DrawPixel(p, Math::Cast(pos * 255));
							}
							break;
						case DrawMode::UVs:
							{
								Vec2<float> uv = Pipeline::InterpolateAttribute(uv1, uv2, uv3, w) * z;
								Vec3<float> temp = { uv.x, uv.y, 0 };
								DrawPixel(p, Math::Cast(temp * 255));
							}
							break;
						case DrawMode::Pattern:
						{
							Vec2<float> uv = Pipeline::InterpolateAttribute(uv1, uv2, uv3, w) * z;
							Vec3<float> normal = Math::Normalize(Pipeline::InterpolateAttribute(normal1, normal2, normal3, w) * z);

							float sample = (fmod(uv.x * this->pattern, 1.0) > 0.5) ^ (fmod(uv.y *this->pattern, 1.0) < 0.5);
							Vec3<float> sampleColor = { sample, sample, sample };
							sampleColor = sampleColor * color;

							float diff = (Math::Dot(normal, { -1, 0, 0 }) + 1) / 2;
							Vec3<float> lightColor = (sampleColor * diff) + (sampleColor * 0.1);
							Math::Clamp(lightColor, 1.0f);

							DrawPixel(p, Math::Cast(lightColor * 255));
						}
						break;
							case DrawMode::Depth:
							{
								Vec3<float> depth = { z, z, z };
								DrawPixel(p, Math::Cast(depth * 255));
							}
						break;
						default:
							break;
						}
					}
				}
			}
		}
	}

	void Raster::DrawObject(Importer::ObjectPtr obj)
	{
		using namespace Importer;
		
		float zNear = this->camera.GetZNear();
		float zFar = this->camera.GetZFar();

		float fovRad = this->camera.GetFov() * (PI / 180.0f);
		float fov = 1.0f / std::tan(fovRad / 2.0f);
		float aspectRatio = this->camera.GetAspectRatio();

		for (const Mesh& mesh : obj->GetMeshes())
		{
			auto vertices = mesh.GetVertices();
			auto normals = mesh.GetNormals();
			auto color = mesh.GetColor();
			Vec3<float> colorF = { (float)(color.x / 255.0f), (float)(color.y / 255.0f), (float)(color.z / 255.0f) };

			for (int i = 0; i < mesh.GetVerticesSize(); i += 9)
			{
				// World space
				Vec3<float> t1 = { vertices[i], vertices[i + 1], vertices[i + 2] };
				Vec3<float> t2 = { vertices[i + 3], vertices[i + 4], vertices[i + 5] };
				Vec3<float> t3 = { vertices[i + 6], vertices[i + 7], vertices[i + 8] };

				// Normals
				Vec3<float> n1 = { normals[i], normals[i + 1], normals[i + 2] };
				Vec3<float> n2 = { normals[i + 3], normals[i + 4], normals[i + 5] };
				Vec3<float> n3 = { normals[i + 6], normals[i + 7], normals[i + 8] };

				// Camera or View Space
				this->camera.ApplyToVertex(t1);
				this->camera.ApplyToVertex(t2);
				this->camera.ApplyToVertex(t3);

				// Positions in the camera space
				Vec3<float> p1 = { t1.x, t1.y, t1.z };
				Vec3<float> p2 = { t2.x, t2.y, t2.z };
				Vec3<float> p3 = { t3.x, t3.y, t3.z };

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

				t1.z = (t1.z - zNear) / (zFar - zNear);
				t2.z = (t2.z - zNear) / (zFar - zNear);
				t3.z = (t3.z - zNear) / (zFar - zNear);

				// Check if triangle is outside the screen
				if (Pipeline::IsOutsideScreen(t1, t2, t3, this->screenSize.x, this->screenSize.y))
					continue;

				if (mode == DrawMode::Wireframe)
					DrawWiredTriangle({t1.x, t1.y}, { t2.x, t2.y }, { t3.x, t3.y }, color);
				else 
					DrawTriangle(t1, t2, t3, n1, n2, n3, p1, p2 , p3, colorF);
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
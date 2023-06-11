#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Drawing {	

	/// <summary>
	/// Used to draw a texture.
	/// </summary>
	class TextureRenderer
	{
		friend class Rasterizer::Window::Window;
	private:
		GPU::ShaderPtr shader;

		GPU::VertexPtr mesh;
	public:
		static void Draw(const GPU::TexturePtr texture);
	private:
		TextureRenderer() {};

		/// <summary>
		/// Returns current instance.
		/// </summary>
		static TextureRenderer& Instance();

		void Init();
		void Release();
	};
}}
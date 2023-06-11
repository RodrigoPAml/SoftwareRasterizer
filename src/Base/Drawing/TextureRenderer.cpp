#include <Rasterizer.hpp>
#include "TextureRenderer.hpp"

namespace Rasterizer {
namespace Drawing {

	void TextureRenderer::Draw(const GPU::TexturePtr texture)
	{
		if (texture == nullptr)
			return;

		auto instance = Instance();

		if (instance.shader == nullptr)
			return;

		if (instance.mesh == nullptr)
			return;

		instance.shader->Use();

		texture->Use(0);

		instance.shader->SetInt("image", 0);

		instance.mesh->Use();
		instance.mesh->Draw(GPU::DrawingType::TRIANGLES);
	}

	TextureRenderer& TextureRenderer::Instance()
	{
		static TextureRenderer* instance = new TextureRenderer();

		return *instance;
	}

	void TextureRenderer::Init()
	{
		const std::string vertShader = { 
			"#version 330 core\n"
			"layout(location = 0) in vec4 vertex;\n"
			"out vec2 uv;\n"
			"void main()\n"
			"{\n"
			"  uv = vertex.zw;\n"
			"  gl_Position = vec4(vertex.xy, 0.0, 1.0);\n"
			"}"
		};

		const std::string fragShader = {
			"#version 330 core\n"
			"layout(location = 0) out vec4 outColor;\n"
			"in vec2 uv;\n"
			"uniform sampler2D image;\n"
			"void main()\n"
			"{\n"
			"  vec4 texFrag = texture(image, uv);\n"
			"  outColor =  vec4(texFrag.xyzw);\n"
			"}"
		};

		this->shader = GPU::ShaderPtr(new GPU::Shader(vertShader, fragShader, ""));

		float vertices[] =
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f
		};

		const GPU::VertexElement element(4);
		const GPU::VertexDescriptor descriptor({{{element}, vertices, GPU::DataUse::STATIC_DRAW, GPU::VertexBufferType::FLOAT}}, 6);

		this->mesh = GPU::VertexPtr(new GPU::Vertex(descriptor));
	}

	void TextureRenderer::Release()
	{
		mesh.~shared_ptr();
		shader.~shared_ptr();
		mesh = nullptr;
		shader = nullptr;
	}
}}
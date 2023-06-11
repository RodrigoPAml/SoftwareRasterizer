#include <Rasterizer.hpp>
#include "Command.hpp"

namespace Rasterizer {
namespace GPU {
namespace Command {

	void EnableVSync()
	{
		glfwSwapInterval(1);
	}

	void DisableVSync()
	{
		glfwSwapInterval(0);
	}


	void SwitchViewPort(const Vec2<int>& pos, const Vec2<int>& size)
	{
		glViewport(pos.x, pos.y, size.x, size.y);
	}

	void Clear()
	{
		glClearColor(0, 0, 0, 0);
		glClear((GLbitfield)GL_COLOR);
	}
}}}

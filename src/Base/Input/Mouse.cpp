#include <Rasterizer.hpp>
#include "Mouse.hpp"

namespace Rasterizer {
namespace Input {

	InputAction Mouse::GetMouseButtonState(const MouseButton button)
	{
		return (InputAction)glfwGetMouseButton(Instance().windowPtr, (int)button);
	}

	Vec2<int> Mouse::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Instance().windowPtr, &xpos, &ypos);

		return {(int)xpos, (int)Window::Window::GetSize().y - (int)ypos};
	}

	Vec2<int> Mouse::GetMouseVariation()
	{
		return Instance().lastPosition -  GetMousePosition();
	}

	void Mouse::SetMouseMode(const MouseMode mode)
	{
		glfwSetInputMode(Instance().windowPtr, GLFW_CURSOR, (int)mode);
	}

	float Mouse::GetScroll()
	{
		auto& mouse = Instance();

		auto& tempScroll = mouse.scroll;

		mouse.scroll = 0;

		return tempScroll;
	}

	bool Mouse::IsMouseInsideWindow()
	{
		return Instance().isInsideWindow;
	}

	Mouse& Mouse::Instance()
	{
		static Mouse* instance = new Mouse();

		return *instance;
	}

	void Mouse::Init(GLFWwindow* windowPtr)
	{
		this->windowPtr = windowPtr;
		this->lastPosition = { 0, 0 };
		this->scroll  = 0;
		this->isInsideWindow = false;
	}

	void Mouse::Release()
	{
		this->lastPosition = { 0, 0 };
		this->scroll = 0;
		this->isInsideWindow = false;
		this->windowPtr = nullptr;
	}
}}

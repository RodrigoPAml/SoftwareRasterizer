#include <Rasterizer.hpp>
#include "Window.hpp"

namespace Rasterizer {
namespace Window {

	void Window::Init(const WindowConfiguration& windowConfig)
	{
		auto& instance = Instance();

		if(!glfwInit())
		{
			instance.isInitialized = false;

			glfwDestroyWindow(instance.windowPtr);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (int)windowConfig.openGlVersionMax);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (int)windowConfig.openGlVersionMin);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		bool HaveMSAA = (windowConfig.windowMSAA > 0);

		if(HaveMSAA) 
			glfwWindowHint(GLFW_SAMPLES, windowConfig.windowMSAA);

		instance.windowPtr = glfwCreateWindow(
			windowConfig.windowSize.x, 
			windowConfig.windowSize.y, 
			windowConfig.windowName.c_str(), 
			NULL, 
			NULL
		);

		if(instance.windowPtr == nullptr)
		{
			instance.isInitialized = false;

			glfwDestroyWindow(instance.windowPtr);
			glfwTerminate();
		}

		glfwMakeContextCurrent(instance.windowPtr);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			instance.isInitialized = false;

			glfwDestroyWindow(instance.windowPtr);
			glfwTerminate();
		}

		glfwSetWindowPos(instance.windowPtr, windowConfig.windowPosition.x, windowConfig.windowPosition.y);

		if(HaveMSAA) 
			glEnable(GL_MULTISAMPLE);

		glViewport(0, 0, Window::GetSize().x, Window::GetSize().y);

		Input::Keyboard::Instance().Init(instance.windowPtr);
		Input::Mouse::Instance().Init(instance.windowPtr);
		Drawing::TextureRenderer::Instance().Init();
		GUI::Init(instance.windowPtr);

		instance.config = windowConfig;
		instance.isInitialized = true;
	}

	void Window::Destroy()
	{
		auto& instance = Instance();

		instance.isFocused = false;
		instance.isHide = false;
		instance.isMinimized = false;
		instance.config = WindowConfiguration();

		Input::Keyboard::Instance().Release();
		Input::Mouse::Instance().Release();
		Drawing::TextureRenderer::Instance().Release();
		GUI::Release();
			
		glfwDestroyWindow(instance.windowPtr);
		glfwTerminate();

		instance.windowPtr = nullptr;
	}

	bool Window::ShouldRun()
	{
		return (Instance().isInitialized && !glfwWindowShouldClose(Instance().windowPtr));
	}

	void Window::Resize(const Vec2<int>& newSize)
	{
		auto& instance = Instance();

		glfwSetWindowSize(instance.windowPtr, newSize.x, newSize.y);

		int x, y;

		glfwGetWindowSize(instance.windowPtr, &x, &y);

		instance.config.windowSize.x = x;
		instance.config.windowSize.y = y;
	}

	Vec2<float> Window::GetSize()
	{
		return Instance().config.windowSize;
	}

	void Window::SetPosition(const Vec2<int>& pos)
	{
		auto& instance = Instance();

		glfwSetWindowPos(instance.windowPtr, pos.x, pos.y);

		int x, y;

		glfwGetWindowPos(instance.windowPtr, &x, &y);

		instance.config.windowPosition.x = x;
		instance.config.windowPosition.y = y;
	}

	Vec2<float> Window::GetPosition()
	{
		return Instance().config.windowPosition;
	}

	std::string Window::GetName()
	{
		return Instance().config.windowName;
	}

	void Window::SetName(const std::string& title)
	{
		auto& instance = Instance();

		glfwSetWindowTitle(instance.windowPtr, title.c_str());
	}

	void Window::SetFullscreen()
	{
		auto& instance = Instance();
		
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwSetWindowMonitor(
			instance.windowPtr, 
			glfwGetPrimaryMonitor(), 
			0, 
			0, 
			mode->width, 
			mode->height,
			mode->refreshRate
		);

		int x, y;

		glfwGetWindowSize(instance.windowPtr, &x, &y);

		instance.config.windowSize.x = x;
		instance.config.windowSize.y = y;

		glfwGetWindowPos(instance.windowPtr, &x, &y);

		instance.config.windowPosition.x = x;
		instance.config.windowPosition.y = y;

		instance.isFullscreen = true;
	}

	void Window::RemoveFullscreen(const Vec2<int>& newSize, const Vec2<int>& newPos)
	{
		auto& instance = Instance();

		glfwSetWindowMonitor(
			instance.windowPtr,
			NULL, 
			0, 
			0, 
			newSize.x, 
			newSize.y, 
			GLFW_DONT_CARE
		);

		int x, y;
		glfwGetWindowSize(instance.windowPtr, &x, &y);

		instance.config.windowSize.x = x;
		instance.config.windowSize.y = y;

		instance.isFullscreen = false;

		instance.SetPosition(newPos);
	}

	void Window::Hide()
	{
		auto& instance = Instance();

		glfwHideWindow(instance.windowPtr);

		instance.isHide = true;
	}

	void Window::Show()
	{
		auto& instance = Instance();

		glfwShowWindow(instance.windowPtr);

		instance.isHide = false;
	}

	void Window::Maximize()
	{
		auto& instance = Instance();

		glfwMaximizeWindow(instance.windowPtr);

		int x, y;

		glfwGetWindowSize(instance.windowPtr, &x, &y);

		instance.config.windowSize.x = x;
		instance.config.windowSize.y = y;

		glfwGetWindowPos(instance.windowPtr, &x, &y);

		instance.config.windowPosition.x = x;
		instance.config.windowPosition.y = y;
	}

	void Window::Minimize()
	{
		auto& instance = Instance();

		glfwIconifyWindow(instance.windowPtr);

		instance.isMinimized = true;
	}

	void Window::Restore()
	{
		auto& instance = Instance();

		glfwRestoreWindow(instance.windowPtr);

		instance.isMinimized = false;
	}

	void Window::Close()
	{
		auto& instance = Instance();

		glfwSetWindowShouldClose(instance.windowPtr, 1);
	}

	void Window::RequestAttention()
	{
		auto& instance = Instance();

		glfwRequestWindowAttention(instance.windowPtr);
	}

	void Window::SwapAndPollEvents()
	{
		auto& instance = Instance();

		auto& mouseIstance = Input::Mouse::Instance();
		mouseIstance.scroll = 0;
		mouseIstance.lastPosition = Input::Mouse::GetMousePosition();

		if(!instance.isInitialized)
			return;

		glfwSwapBuffers(instance.windowPtr);
		glfwPollEvents();
	}

	bool Window::IsMinimized()
	{
		return Instance().isMinimized;
	}

	bool Window::IsHide()
	{
		return Instance().isHide;
	}

	bool Window::IsFullscreen()
	{
		return Instance().isFullscreen;
	}

	bool Window::IsFocused()
	{
		return Instance().isFocused;
	}

	Vec2<int> Window::GetScreenLimits()
	{
		auto& instance = Instance();

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		return {mode->width, mode->height};
	}

	Window& Window::Instance()
	{
		static Window* instance = new Window();

		return *instance;
	}
}}

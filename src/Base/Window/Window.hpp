#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Window {

	/// <summary>
	/// Class to manager the window.
	/// This class is a singleton.
	/// </summary>
	class Window
	{
	private:
		/// <summary>
		/// GLFW window reference.
		/// </summary>
		GLFWwindow* windowPtr;

		/// <summary>
		/// Window current configuration.
		/// </summary>
		WindowConfiguration config;

		/// <summary>
		/// Window states.
		/// </summary>
		bool isInitialized;
		bool isMinimized;
		bool isFullscreen;
		bool isHide;
		bool isFocused;
	public:
		/// <summary>
		/// Initialize window with GLFW, OpenGL and GLAD.
		/// </summary>
		static void Init(const WindowConfiguration& windowConfig = WindowConfiguration());

		/// <summary>
		/// Destroy window with GLFW, OpenGL and GLAD.
		/// </summary>
		static void Destroy();

		/// <summary>
		/// Returns if the main loop of the window should continue.
		/// </summary>
		/// <returns></returns>
		static bool ShouldRun();

		static void Resize(const Vec2<int>& newSize);
		static Vec2<float> GetSize();

		static void SetPosition(const Vec2<int>& pos);
		static Vec2<float> GetPosition();

		static std::string GetName();
		static void SetName(const std::string& title);

		static void SetFullscreen();
		static void RemoveFullscreen(const Vec2<int>& newSize, const Vec2<int>& newPos);

		static void Hide();
		static void Show();

		static void Maximize();
		static void Minimize();
		static void Restore();
		static void Close();

		static void RequestAttention();
		static void SwapAndPollEvents();

		static bool IsMinimized();
		static bool IsHide();
		static bool IsFullscreen();
		static bool IsFocused();

		static Vec2<int> GetScreenLimits();
	private:
		Window() {};
		Window(Window const&);

		/// <summary>
		/// Returns current instance.
		/// </summary>
		/// <returns></returns>
		static Window& Instance();
	};
}}

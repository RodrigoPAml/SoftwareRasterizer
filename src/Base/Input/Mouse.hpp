#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Input {

	/// <summary>
	/// A class to read the mouse input.
	/// This class is a Singleton.
	/// </summary>
	class Mouse
	{
		friend class Rasterizer::Window::Window;
	private:
		/// <summary>
		/// The mouse last saved position.
		/// Used to calculate mouse delta.
		/// </summary>
		Vec2<int> lastPosition;

		/// <summary>
		/// The frame scroll of the mouse.
		/// </summary>
		float scroll;

		/// <summary>
		/// If the mouse is inside the display
		/// </summary>
		bool isInsideWindow;

		/// <summary>
		/// Reference to current GLFW Window in use.
		/// </summary>
		GLFWwindow* windowPtr;
	public:
		/// <summary>
		/// Get the current state of some mouse button.
		/// </summary>
		static InputAction GetMouseButtonState(const MouseButton button);

		/// <summary>
		/// Returns the current mouse position.
		/// </summary>
		static Vec2<int> GetMousePosition();

		/// <summary>
		/// Returns the current mouse delta.
		/// </summary>
		static Vec2<int> GetMouseVariation();

		/// <summary>
		/// Sets the mouse visualization mode.
		/// </summary>
		static void SetMouseMode(const MouseMode mode);

		/// <summary>
		/// Get the mouse scroll.
		/// Based on current frame.
		/// </summary>
		static float GetScroll();

		/// <summary>
		/// Get if the mouse is inside the window.
		/// </summary>
		static bool IsMouseInsideWindow();
	private:
		Mouse() {};
		Mouse(Mouse const&);

		/// <summary>
		/// Returns current instance.
		/// </summary>
		static Mouse& Instance();

		/// <summary>
		/// State control.
		/// </summary>
		void Init(GLFWwindow* windowPtr);
		void Release();
	};
}}
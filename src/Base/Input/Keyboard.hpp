 #pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Input {

	/// <summary>
	/// A class to read the keyboard input.
	/// This class is a Singleton.
	/// </summary>
	class Keyboard
	{
		friend class Rasterizer::Window::Window;
	private:
		/// <summary>
		/// To manage keys.
		/// </summary>
		std::set<KeyboardKey> frameClickedKeys;

		/// <summary>
		/// Modifiers
		/// </summary>
		std::set<KeyModifier> frameClickedMods;

		/// <summary>
		/// Reference to current GLFW Window in use.
		/// </summary>
		GLFWwindow* windowPtr;
	public:
		/// <summary>
		/// Get state of an key.
		/// </summary>
		static InputAction GetKeyState(const KeyboardKey key);

		/// <summary>
		/// Get modifier state.
		/// </summary>
		static InputAction GetModState(const KeyModifier mod);
	private:
		Keyboard() {};
		Keyboard(Keyboard const&) {};

		/// <summary>
		/// Returns current instance.
		/// </summary>
		static Keyboard& Instance();

		void Init(GLFWwindow* windowPtr);
		void Release();

		/// <summary>
		/// Recieve events directly from GLFW.
		/// Internal usage.
		/// </summary>
		static void MasterKeyboardEventCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
	};
}}


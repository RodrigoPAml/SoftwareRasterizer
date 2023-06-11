#include <Rasterizer.hpp>
#include "Keyboard.hpp"

namespace Rasterizer {
namespace Input {

	InputAction Keyboard::GetKeyState(const KeyboardKey key)
	{
		auto& instance = Instance();

		if(instance.frameClickedKeys.find(key) != instance.frameClickedKeys.end())
			return InputAction::REPEAT;

		return (InputAction)glfwGetKey(instance.windowPtr, (int)key);
	}

	InputAction Keyboard::GetModState(const KeyModifier mod)
	{
		auto& instance = Instance();

		if (instance.frameClickedMods.find(mod) != instance.frameClickedMods.end())
			return InputAction::PRESS;

		return InputAction::RELEASE;
	}

	Keyboard& Keyboard::Instance()
	{
		static Keyboard* keyboard = new Keyboard();

		return *keyboard;
	}

	void Keyboard::Init(GLFWwindow* windowPtr)
	{
		this->windowPtr = windowPtr;

		glfwSetKeyCallback(windowPtr, MasterKeyboardEventCallback);
	}

	void Keyboard::Release()
	{
		glfwSetKeyCallback(windowPtr, nullptr);

		this->frameClickedKeys.clear();
		this->frameClickedMods.clear();
		this->windowPtr = nullptr;
	}

	void Keyboard::MasterKeyboardEventCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
	{
		auto& keyboard = Instance();
		
		if((InputAction)action == InputAction::PRESS && mod != 0)
			keyboard.frameClickedMods.insert((KeyModifier)mod);

		if ((InputAction)action == InputAction::REPEAT)
		{
			keyboard.frameClickedKeys.insert((KeyboardKey)key);
			
			if (mod != 0)
				keyboard.frameClickedMods.insert((KeyModifier)mod);
		}
		else if ((InputAction)action == InputAction::RELEASE)
			keyboard.frameClickedKeys.erase((KeyboardKey)key);

		if (mod == 0)
			keyboard.frameClickedMods.clear();
	}
}}

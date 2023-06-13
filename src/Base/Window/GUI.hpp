#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Window {

	/// <summary>
	/// Manager GUI for the engine.
	/// </summary>
	class GUI
	{
		friend class Window;
	private:
		ImGuiContext* context;

		int fontSize = 26;
		float fontScale = 1.0f;
	public:
		// Frame limiters
		static void BeginFrame();
		static void EndFrame();

		// Ids
		static void Push(const std::string& label);
		static void Pop();

		// Texts
		static void Text(const std::string& label);
		static void DisabledText(const std::string& label);
		static void BulletText(const std::string& label);
		static void ColoredText(const std::string& label, const Vec4<float>& color);
		static void WrappedText(const std::string& label);

		// Buttons and Selectables
		static bool CheckBox(const std::string& label, bool& checked);
		static bool Button(const std::string& label, const Vec2<float>& size = { 0, 0 });
		static bool RadioButton(const std::string& label, bool& selected);
		static bool Selectable(const std::string& label, const std::string& text, bool& selected);
		static bool Selectable(const std::string& label, const std::string& text);

		// Images
		static void Image(GPU::TexturePtr texture, const Vec2<float>& size);
		static bool ImageButton(const std::string& label, GPU::TexturePtr texture);

		// Inputs
		static bool Input(const std::string& label, std::string& text);
		static bool Input(const std::string& label, const std::string& hint, std::string& text);
		static bool Input(const std::string& label, double& val);
		static bool Input(const std::string& label, float& val);
		static bool Input(const std::string& label, int& val);
		static bool Input(const std::string& label, Vec2<float>& val);
		static bool Input(const std::string& label, Vec3<float>& val);
		static bool Input(const std::string& label, Vec4<float>& val);

		static bool MultilineText(const std::string& label, std::string& text);

		// Drags
		static bool Drag(const std::string& label, int& val);
		static bool Drag(const std::string& label, float& val);
		static bool Drag(const std::string& label, Vec2<float>& val);
		static bool Drag(const std::string& label, Vec3<float>& val);
		static bool Drag(const std::string& label, Vec4<float>& val);

		// Sliders
		static bool Slider(const std::string& label, const Vec2<int>& limits, int& val);
		static bool Slider(const std::string& label, const Vec2<float>& limits, float& val);
		static bool Slider(const std::string& label, const Vec2<int>& limits, Vec2<int>& val);
		static bool Slider(const std::string& label, const Vec2<float>& limits, Vec2<float>& val);
		static bool Slider(const std::string& label, const Vec2<float>& limits, Vec3<float>& val);
		static bool Slider(const std::string& label, const Vec2<float>& limits, Vec4<float>& val);

		// Color
		static bool ColorSelectable(const std::string& label, Vec3<float>& color);
		static bool ColorSelectable(const std::string& label, Vec4<float>& color);

		// List box
		static bool BeginListBox(const std::string& label);
		static void EndListBox();

		// Combo box
		static bool ComboBox(const std::string& label, const std::vector<std::string>& itens, int& currItem, const std::string& filter = "");

		// Tabs
		static bool BeginTabBar(const std::string& label);
		static void EndTabBar();

		static bool BeginTabItem(const std::string& label);
		static void EndTabItem();

		// Trees
		static bool BeginTreeNode(const std::string& label , const std::string& text);
		static void EndTreeNode();

		// Font Scale
		static void SetFontScale(float scale);
		static float GetFontScale();
		static Vec2<float> CalculateTextSize(const std::string& text);

		// Window Components
		static bool IsCurrentWindowAppearing();
		static bool IsCurrentWindowCollapsed();
		static bool IsCurrentWindowFocused();
		static bool IsCurrentWindowHovered();

		static void SetNextWindowPosition(const Vec2<float>& pos);
		static void SetNextWindowSize(const Vec2<float>& size);
		static void SetWindowPosition(const Vec2<float>& pos);
		static void SetWindowSize(const Vec2<float>& size);

		static Vec2<float> GetWindowPosition();
		static Vec2<float> GetWindowSize();

		static bool BeginWindow(const std::string& label, bool* open = nullptr, const std::set<GUIWindowFlags>& flags = { GUIWindowFlags::None });
		static void EndWindow();
		static bool BeginInnerWindow(const std::string& label, const Vec2<float>& size, const std::set<GUIWindowFlags>& flags = { GUIWindowFlags::None });
		static void EndInnerWindow();

		static void DownScroll();

		// Hint window
		static void BeginHintWindow();
		static void EndHintWindow();

		// Pop Ups
		static bool BeginPopUp(const std::string& label);
		static void EndPopUp();
		static void OpenPopUp(const std::string& label);
		static void CloseCurrentPopUp();
		static bool IsPopUpOpened(const std::string& label);

		// Header and identation
		static bool Header(const std::string& label);
		static void Ident(float size);
		static void Unident(float size);

		// Layouts
		static void ContinueSameLine(const float spacing = -1);
		static void Separator();
		static void Space();

		// GUI State
		static bool IsCurrentItemClickedLeft();
		static bool IsCurrentItemClickedRight();
		static bool IsCurrentItemActive();
		static bool IsCurrentItemFocused();
		static bool IsCurrentItemHovered();

		static bool IsLeftMouseClicked();
		static bool IsRightMouseClicked();

		static void SetNextItemWidth(float width);

		// Menus
		static bool BeginMainMenuBar();
		static void EndMainMenuBar();

		static bool BeginMenuBar();
		static void EndMenuBar();

		static bool BeginMenu(const std::string& label, const bool enabled = true);
		static void EndMenu();

		static bool MenuItem(const std::string& label, const bool enabled = true, const std::string& shortcut = "");

		// Drag and Drop
		static bool BeginSourceDragDrop();
		static void EndSourceDragDrop();

		static bool BeginDestinyDragDrop();
		static void EndDestinyDragDrop();

		static void SetDragDropData(const std::string& label, std::string data);
		static std::string GetDragDropData(const std::string& label);

		// Tables
		static bool BeginTable(const std::string& label, unsigned int columns);
		static void EndTable();
		static void NextRow();
		static void NextColumn();

		static int GetFontSize();
	private:
		GUI() {};
		GUI(GUI const&) {};

		/// <summary>
		/// Returns current instance.
		/// </summary>
		/// <returns></returns>
		static GUI& Instance();

		/// <summary>
		/// Init and Release GUI.
		/// </summary>
		static void Init(GLFWwindow* windowPtr);
		static void Release();
	};
}}
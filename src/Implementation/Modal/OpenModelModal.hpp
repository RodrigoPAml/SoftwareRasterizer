#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer
{
	class OpenModelModal
	{
	private:
		std::string startingPath = "C:/Users";
		bool fileDialogOpen = false;
	public:
		OpenModelModal() = default;
		~OpenModelModal() = default;

		std::string Draw();
	private:
		std::wstring OpenFileDialog();
	};
}

#include <Rasterizer.hpp>

int main()
{
	using namespace Rasterizer;
	using namespace Input;
	using Window = Window::Window;

	Window::Init();
	Window::Maximize();

	OpenModelModal modal;
	auto modelPath = modal.Draw();

	if (modelPath == "")
	{
		std::cout << "Empty model to open" << std::endl;
		return 0;
	}

	auto obj = Importer::Importer::Load(modelPath);

	if (obj == nullptr)
	{
		std::cout << "Fail to open " << modelPath << std::endl;
		return 0;
	}

	Raster raster = Raster({400, 300});

	while (Window::ShouldRun())
	{
		raster.BeginDraw();
		raster.DrawObject(obj);
		raster.EndDraw();

		Window::SwapAndPollEvents();
	}

	Window::Close();
}
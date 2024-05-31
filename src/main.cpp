#include <Rasterizer.hpp>

int main()
{
	using namespace Rasterizer;
	using namespace Input;
	using Window = Window::Window;

	Window::Init();
	Window::Maximize();

	std::string objName = "sibenik";
	Importer::ObjectPtr obj = Importer::Importer::Load(Utils::Directory::GetCurrentPath() + "\\..\\..\\models\\" + objName + "\\" + objName + ".obj");

	if(obj == nullptr)
		obj = Importer::Importer::Load(Utils::Directory::GetCurrentPath() + "\\" + objName + "\\" + objName + ".obj");

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
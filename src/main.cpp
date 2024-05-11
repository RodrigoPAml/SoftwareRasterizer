#include <Rasterizer.hpp>

int main()
{
	using namespace Rasterizer;
	using namespace Input;
	using Window = Window::Window;

	Window::Init();
	Window::Maximize();

	Importer::ObjectPtr obj = Importer::Importer::Load(Utils::Directory::GetCurrentPath() + "\\..\\..\\models\\scene\\scene.obj");
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
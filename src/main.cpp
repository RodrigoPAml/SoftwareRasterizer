#include <Rasterizer.hpp>

int main()
{
	using namespace Rasterizer;
	using namespace Input;
	using Window = Window::Window;

	Window::Init();
	Window::Maximize();

	Importer::ObjectPtr obj = Importer::Importer::Load("C:\\Users\\Rodrigo\\Desktop\\untitled.obj");
	Raster raster = Raster(1900, 1000);

	while (Window::ShouldRun())
	{
		raster.BeginDraw();
		raster.DrawObject(obj);
		raster.EndDraw();

		Window::SwapAndPollEvents();
	}

	Window::Close();
}
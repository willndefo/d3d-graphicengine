#include "Core/Window.h"
#include <memory>

int main()
{
	std::unique_ptr<GWindow> window(new GWindow(1280, 720, "D3D graphics engine"));

	window->Init();

	while (window->IsVisible())
	{
		window->Run();
	}

	return 0;
}
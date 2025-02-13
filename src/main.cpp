#include <memory>
#include "Core/Window.h"
#include "Core/Renderer.h"

int main()
{
	GWindow* window{ new GWindow(1280, 720, "D3D graphics engine") };
	window->Init();

	GRenderer* renderer{ new GRenderer(window) };

	while (window->IsVisible())
	{
		window->Run();
		renderer->ClearRenderTargetView({ 0.2f, 0.3f, 0.4f, 1.0f });
		renderer->Present();
	}

	delete window;
	delete renderer;

	return 0;
}
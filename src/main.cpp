#include <memory>
#include "Core/Window.h"
#include "Core/RendererManager.h"
#include "Core/Object.h"
#include <vector>

/*
	Draw triangle in the clockwise order
*/

VertexData vertices1[] = {
	{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) }
};

VertexData vertices2[] = {
	{ XMFLOAT3(0.0f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) }
};


uint32_t indices[] = {
	0, 1, 2
};

int main()
{
	constexpr uint32_t indexCount = sizeof(indices) / sizeof(*indices);

	GWindow* window{ new GWindow(1280, 720, "D3D graphics engine") };
	window->Init();

	GRenderer* renderer{ GRendererManager::CreateRenderer(window)};

	/// Objects array
	std::vector<GObject*> objects;
	
	GObject* triangle1{ new GObject(vertices1, indices, indexCount) };
	GObject* triangle2{ new GObject(vertices2, indices, indexCount) };
	objects.push_back(triangle1);
	objects.push_back(triangle2);

	/// Renderer loop
	while (window->IsVisible())
	{
		window->Run();
		renderer->ClearRenderTargetView({ 0.2f, 0.3f, 0.4f, 1.0f });
		renderer->SetPipeline();

		for (GObject* object : objects)
		{
			object->SetProps();
			renderer->Draw(object->GetIndexCount());
		}
		
		renderer->Present();
	}

	delete window;
	delete renderer;

	return 0;
}
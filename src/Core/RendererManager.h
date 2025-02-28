#pragma once

#include "Renderer.h"
#include "utilities.h"


class GRendererManager
{
private:
	static inline GRenderer* Renderer = nullptr;

public:
	GRendererManager() = default;
	~GRendererManager() = default;

	static GRenderer* CreateRenderer(GWindow* Window)
	{
		if (Renderer)
		{
			DEBUG_LOG(LOG_WARNING, "Renderer is already initialized.");
		}

		Renderer = new GRenderer(Window);
		return Renderer;
	}

	static GRenderer* GetRenderer() { 
		if (!Renderer)
		{
			DEBUG_LOG(LOG_ERROR, "Renderer is not initialized.");
			abort();
		}

		return Renderer; 
	}
};
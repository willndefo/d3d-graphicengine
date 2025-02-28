#pragma once

#include "RendererManager.h"

struct VertexData
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

class GObject
{
private:
	ComPtr<ID3D11Buffer> VertexBuffer;
	ComPtr<ID3D11Buffer> IndexBuffer;
	uint32_t IndexCount;

	const GRenderer* Renderer = nullptr;

public:
	GObject(VertexData* VerticesData, uint32_t* IndicesData, uint32_t NumIndices);
	~GObject() = default;

	void SetProps();

	uint32_t GetIndexCount() { return IndexCount; }
};
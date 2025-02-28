#include "Object.h"
#include "Renderer.h"

GObject::GObject(VertexData* VerticesData, uint32_t* IndicesData, uint32_t NumIndices)
{
	Renderer = GRendererManager::GetRenderer();
	IndexCount = NumIndices;

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = 3 * sizeof(VertexData);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
	vertexSubresourceData.pSysMem = VerticesData;
	vertexSubresourceData.SysMemPitch = 0;
	vertexSubresourceData.SysMemSlicePitch = 0;

	Renderer->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, VertexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = 3 * sizeof(uint32_t);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
	indexSubresourceData.pSysMem = IndicesData;
	indexSubresourceData.SysMemPitch = 0;
	indexSubresourceData.SysMemSlicePitch = 0;

	Renderer->GetDevice()->CreateBuffer(&indexBufferDesc, &indexSubresourceData, IndexBuffer.GetAddressOf());
}

void GObject::SetProps()
{
	uint32_t stride = sizeof(VertexData);
	uint32_t offset = 0;

	Renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &stride, &offset);
	Renderer->GetDeviceContext()->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

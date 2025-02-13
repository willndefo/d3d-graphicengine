#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>


using namespace DirectX;
using namespace Microsoft::WRL;


class GWindow;

class GRenderer
{
private:
	GWindow* Window;
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;
	ComPtr<IDXGISwapChain> SwapChain;
	ComPtr<ID3D11RenderTargetView> RenderTargetView;

	ComPtr<ID3D11VertexShader> VertexShader;
	ComPtr<ID3DBlob> VertexShaderBlob;
	ComPtr<ID3D11PixelShader> PixelShader;
	ComPtr<ID3DBlob> PixelShaderBlob;

	ComPtr<ID3D11InputLayout> InputLayout;

public:
	GRenderer(GWindow* InWindow);
	~GRenderer() = default;

	// Take rgba values the range 0-1
	void ClearRenderTargetView(XMFLOAT4 Color);

	// Take rgba values in the range 0-255
	// void ClearRenderTargetView(XMUINT4 Color);

	void Draw(uint32_t indexCount);

	void Present();

	void SetPipeline();

	ComPtr<ID3D11Device> GetDevice() const;
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const;

private:
	void CreateDevice();
	void CreateSwapChain();
	void CreateRenderTargetView();
	void CreateShaders();
	void CreateInputLayout();
};
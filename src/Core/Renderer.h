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

public:
	GRenderer(GWindow* InWindow);
	~GRenderer() = default;

	void CreateDevice();
	void CreateSwapChain();
	void CreateRenderTargetView();

	// Take rgba values the range 0-1
	void ClearRenderTargetView(XMFLOAT4 Color);

	// Take rgba values in the range 0-255
	// void ClearRenderTargetView(XMUINT4 Color);

	void Present();
};
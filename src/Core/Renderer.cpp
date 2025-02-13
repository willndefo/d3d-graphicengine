#include "Renderer.h"
#include "Window.h"
#include "utilities.h"

GRenderer::GRenderer(GWindow* InWindow) 
	: Window(InWindow),
	Device(nullptr),
	DeviceContext(nullptr),
	SwapChain(nullptr),
	RenderTargetView(nullptr)
{
	CreateDevice();
	CreateSwapChain();
	CreateRenderTargetView();
}

void GRenderer::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(D3D11CreateDevice(
		/* Adapater= */ nullptr,
		/* DriverType= */ D3D_DRIVER_TYPE_HARDWARE,
		/* Module= */ nullptr,
		/* Flags= */ 0,
		featureLevels,
		/* SDKVersion= */ 1,
		D3D11_SDK_VERSION,
		Device.GetAddressOf(),
		nullptr,
		DeviceContext.GetAddressOf()
	)))
	{
		DEBUG_LOG(LOG_ERROR, "Failed to create D3D11 Device and Context !");
		abort();
	}

	DEBUG_LOG(LOG_INFO, "Device and Context successfully created.");
}

void GRenderer::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = Window->GetWidth();
	swapChainDesc.BufferDesc.Height = Window->GetHeight();
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = Window->GetWindowNativeHandler();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;

	ComPtr<IDXGIDevice>	dxgiDevice;
	Device.As(&dxgiDevice);

	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());

	ComPtr<IDXGIFactory> dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	if (FAILED(dxgiFactory->CreateSwapChain(Device.Get(), &swapChainDesc, SwapChain.GetAddressOf())))
	{
		DEBUG_LOG(LOG_ERROR, "Failed to create swap chain !");
		abort();
	}

	DEBUG_LOG(LOG_INFO, "Swapchain successfully created.");
}

void GRenderer::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> colorBuffer;

	SwapChain->GetBuffer(0, IID_PPV_ARGS(&colorBuffer));

	if (FAILED(Device->CreateRenderTargetView(colorBuffer.Get(), nullptr, RenderTargetView.GetAddressOf())))
	{
		DEBUG_LOG(LOG_ERROR, "Failed to create render target view !");
		abort();
	}

	DEBUG_LOG(LOG_INFO, "Render target view successfully created.");
}

void GRenderer::ClearRenderTargetView(XMFLOAT4 Color)
{
	const float clearColor[] = { Color.x, Color.y, Color.z, Color.w };
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), clearColor);
}

void GRenderer::Present()
{
	SwapChain->Present(/* vsyn= */1, /* Flags= */0);
}

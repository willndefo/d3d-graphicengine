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
	CreateShaders();
	CreateInputLayout();
}

void GRenderer::ClearRenderTargetView(XMFLOAT4 Color)
{
	const float clearColor[] = { Color.x, Color.y, Color.z, Color.w };
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), clearColor);
}

void GRenderer::Draw(uint32_t indexCount)
{
	DeviceContext->DrawIndexed(indexCount, 0, 0);
}

void GRenderer::Present()
{
	SwapChain->Present(/* vsync = */1, /* Flags= */0);
}

void GRenderer::SetPipeline()
{
	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), nullptr);
	DeviceContext->PSSetShader(PixelShader.Get(), nullptr, 0);
	DeviceContext->VSSetShader(VertexShader.Get(), nullptr, 0);
	DeviceContext->IASetInputLayout(InputLayout.Get());
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = Window->GetWidth();
	viewport.Height = Window->GetHeight();
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	DeviceContext->RSSetViewports(1, &viewport);
}

ComPtr<ID3D11Device> GRenderer::GetDevice() const
{
	return Device;
}

ComPtr<ID3D11DeviceContext> GRenderer::GetDeviceContext() const
{
	return DeviceContext;
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

void GRenderer::CreateShaders()
{
	ComPtr<ID3DBlob> errorBlob;
	const std::string pixelShaderCode = GUtilities::ReadHLSLFile("PS_Test.hlsl");

	D3DCompile(pixelShaderCode.c_str(), pixelShaderCode.length(), nullptr, nullptr, nullptr, PS_ENTRYPOINT, PS_VERSION,
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &PixelShaderBlob, &errorBlob);

	if (errorBlob.Get() != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		DEBUG_LOG(LOG_ERROR, "%s", (char*)errorBlob->GetBufferPointer());
	}

	if (FAILED(Device->CreatePixelShader(PixelShaderBlob->GetBufferPointer(), PixelShaderBlob->GetBufferSize(), nullptr, PixelShader.GetAddressOf())))
	{
		DEBUG_LOG(LOG_ERROR, "Failed to create pixel shader.");
		abort();
	}

	const std::string vertexShaderCode = GUtilities::ReadHLSLFile("VS_Test.hlsl");

	D3DCompile(vertexShaderCode.c_str(), vertexShaderCode.length(), nullptr, nullptr, nullptr, VS_ENTRYPOINT, VS_VERSION,
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &VertexShaderBlob, &errorBlob);

	if (errorBlob.Get() != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		DEBUG_LOG(LOG_ERROR, "%s", (char*)errorBlob->GetBufferPointer());
	}

	if (FAILED(Device->CreateVertexShader(VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), nullptr, VertexShader.GetAddressOf())))
	{
		DEBUG_LOG(LOG_ERROR, "Failed to create vertex shader.");
		abort();
	}
}

void GRenderer::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	Device->CreateInputLayout(inputElementDesc, 2, VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), InputLayout.GetAddressOf());
}
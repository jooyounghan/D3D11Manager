#include "GEngine.h"

#include <exception>

using namespace std;
using namespace D3D11;

GEngine* GEngine::GetInstance()
{
	static GEngine engine;
	return &engine;
}

void GEngine::InitEngine(
    UINT widthIn,
    UINT heightIn,
    UINT refreshNumerator,
    UINT refreshDenominator,
    DXGI_FORMAT backBufferFormat,
    UINT backBufferCount,
    HWND wndHandle,
    DXGI_SWAP_EFFECT swapEffect,
    DXGI_SWAP_CHAIN_FLAG swapChainFlag
)
{
    m_backBufferCount = backBufferCount;
    m_backBufferFormat = backBufferFormat;
    m_swapChainFlag = swapChainFlag;

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

    swapChainDesc.BufferDesc.Width = widthIn;
    swapChainDesc.BufferDesc.Height = heightIn;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = refreshNumerator;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = refreshDenominator;
    swapChainDesc.BufferDesc.Format = backBufferFormat;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
    swapChainDesc.BufferCount = backBufferCount;
    swapChainDesc.OutputWindow = wndHandle;
    swapChainDesc.Windowed = true;
    swapChainDesc.SwapEffect = swapEffect;
    swapChainDesc.Flags = swapChainFlag;

    constexpr D3D_DRIVER_TYPE	DriverType = D3D_DRIVER_TYPE_HARDWARE;
    constexpr D3D_FEATURE_LEVEL FeatureLevels[2] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };

    D3D_FEATURE_LEVEL selectedFeatureLevel;
    HRESULT hResult = D3D11CreateDeviceAndSwapChain(
        NULL,
        DriverType,
        NULL,
        CreateDeviceFlags,
        FeatureLevels,
        1,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        m_swapChain.GetAddressOf(),
        m_device.GetAddressOf(),
        &selectedFeatureLevel,
        m_deviceContext.GetAddressOf()
    );

    if (FAILED(hResult)) { throw exception("D3D11CreateDeviceAndSwapChain Failed"); }

    InitBackBuffer();
}

void GEngine::ResizeSwapChain(UINT widthIn, UINT heightIn)
{

    m_backBufferTexture.Reset();
    m_backBufferRTV.Reset();

    m_deviceContext->Flush();

    m_swapChain->ResizeBuffers(
        m_backBufferCount,
        widthIn, heightIn,
        m_backBufferFormat,
        m_swapChainFlag
    );

    InitBackBuffer();
}

void GEngine::InitBackBuffer()
{
    HRESULT hResult = m_swapChain->GetBuffer(0, IID_PPV_ARGS(m_backBufferTexture.GetAddressOf()));
    if (FAILED(hResult)) { throw exception("GetBuffer From SwapChain Failed"); }

    hResult = m_device->CreateRenderTargetView(m_backBufferTexture.Get(), nullptr, m_backBufferRTV.GetAddressOf());
    if (FAILED(hResult)) { throw exception("CreateRenderTargetView From SwapChain BackBuffer Failed"); }
}

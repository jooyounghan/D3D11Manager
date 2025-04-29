#include "TestApp.h"
#include "GEngine.h"
#include "DynamicBuffer.h"

#include <iostream>

using namespace std;
using namespace App;
using namespace D3D11;

CTestApp::CTestApp()
	: App::CBaseApp()
{

}

CTestApp* CTestApp::GetInstance() noexcept
{
	static CTestApp testApp;
	return &testApp;
}

void CTestApp::Init(
	UINT width,
	UINT height,
	const wchar_t* className,
	const wchar_t* applicaitonName
)
{
	CBaseApp::Init(width, height, className, applicaitonName);

	D3D11::GEngine* engine = D3D11::GEngine::GetInstance();
	engine->InitEngine(m_width, m_height, 240, 1,
		DXGI_FORMAT_R8G8B8A8_UNORM, 2,
		m_mainWindow,
		DXGI_SWAP_EFFECT_FLIP_DISCARD,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
	);
}

void CTestApp::Update(float deltaTime)
{
	static FLOAT clearColor[4] = { 0.f, 0.f, 0.f, 1.f };
	D3D11::GEngine* engine = D3D11::GEngine::GetInstance();

	clearColor[0] += deltaTime * 0.1f;

	ID3D11DeviceContext* deviceContext = engine->GetDeviceContext();
	deviceContext->ClearRenderTargetView(engine->GetBackBufferRTV(), clearColor);

	engine->GetSwapChain()->Present(1, 0);
}


void CTestApp::Quit()
{
}

void CTestApp::AppProcImpl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
}

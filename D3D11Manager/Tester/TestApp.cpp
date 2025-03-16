#include "TestApp.h"
#include "GEngine.h"
#include "DynamicBuffer.h"

#include <iostream>

CTestApp::CTestApp()
	: D3D11::CBaseApp()
{

}

CTestApp* CTestApp::GetInstance() noexcept
{
	static CTestApp testApp;
	return &testApp;
}

void CTestApp::Init(const UINT& width, const UINT& height, const wchar_t* className, const wchar_t* applicaitonName) noexcept
{
	CBaseApp::Init(width, height, className, applicaitonName);

}

void CTestApp::Update(const float& deltaTime)
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

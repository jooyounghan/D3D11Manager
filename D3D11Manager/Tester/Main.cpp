#include "TestApp.h"
#include "GEngine.h"

int main()
{
	CTestApp* testApp = CTestApp::GetInstance();
	testApp->Init(1280, 960, L"Test", L"Engine");

	D3D11::GEngine* engine = D3D11::GEngine::GetInstance();
	engine->InitEngine(1280, 960, 240, 1,
		DXGI_FORMAT_R8G8B8A8_UNORM, 2,
		testApp->GetWindowHandle(),
		DXGI_SWAP_EFFECT_FLIP_DISCARD,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
	);

	testApp->Run();
	testApp->Quit();
}
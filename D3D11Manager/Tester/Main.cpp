#include "TestApp.h"
#include "GEngine.h"

int main()
{
	UINT AppWidth = 1920;
	UINT AppHeight = 1080;

	CTestApp* testApp = CTestApp::GetInstance();

	UINT& AppWidthRef = testApp->GetWidth();
	UINT& AppHeightRef = testApp->GetHeight();

	testApp->Init(AppWidth, AppHeight, L"Test", L"Engine");
	testApp->Run();
	testApp->Quit();
}
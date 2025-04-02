#include "BaseApp.h"

using namespace App;

CBaseApp* CBaseApp::MainApp = nullptr;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return CBaseApp::MainApp->AppProc(hWnd, msg, wParam, lParam);
}

CBaseApp::CBaseApp() noexcept
{
	ZeroMemory(&m_windowClass, sizeof(WNDCLASSEX));
	ZeroMemory(&m_frequency, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_prevTime, sizeof(LARGE_INTEGER));
	CBaseApp::MainApp = this;
}

void CBaseApp::Run()
{
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update(GetDeltaTime());
		}
	}
}

void CBaseApp::Create(
	UINT width, 
	UINT height,
	const wchar_t* className, 
	const wchar_t* applicaitonName
) noexcept
{
	m_width = width;
	m_height = height;

	ZeroMemory(&m_windowClass, sizeof(m_windowClass));
	m_windowClass = {
		sizeof(WNDCLASSEX), CS_CLASSDC, WndProc,
		0L, 0L, GetModuleHandle(NULL),
		NULL, NULL, NULL,
		NULL, className, NULL
	};
	RegisterClassEx(&m_windowClass);

	HWND hWindow = CreateWindow(
		m_windowClass.lpszClassName, applicaitonName,
		WS_OVERLAPPEDWINDOW, 0, 0,
		m_width, m_height, NULL,
		NULL, m_windowClass.hInstance, NULL
	);
	m_mainWindow = hWindow;
	ShowWindow(m_mainWindow, SW_SHOW);

	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_prevTime);
}

LRESULT __stdcall CBaseApp::AppProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_EXITSIZEMOVE:
		OnWindowSizeUpdate();
		break;
	case WM_CREATE:
		DragAcceptFiles(hWnd, TRUE);
		break;
	}
	AppProcImpl(hWnd, msg, wParam, lParam);
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

void CBaseApp::OnWindowSizeUpdate() noexcept
{
	RECT Rect;
	if (GetClientRect(m_mainWindow, &Rect))
	{
		m_width = Rect.right - Rect.left;
		m_height = Rect.bottom - Rect.top;
		m_wndSizeUpdateHandler(m_width, m_height);
	}
}

float CBaseApp::GetDeltaTime() noexcept
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	LONGLONG elapsed = currentTime.QuadPart - m_prevTime.QuadPart;
	const float deltaTime = static_cast<float>(elapsed) / m_frequency.QuadPart;

	m_prevTime = currentTime;
	return deltaTime;
}

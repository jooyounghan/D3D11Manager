#pragma once
#include "BaseApp.h"

class CTestApp : public D3D11::CBaseApp
{
private:
	CTestApp();
	CTestApp(const CTestApp& testApp) = delete;
	CTestApp(CTestApp&& testApp) = delete;

public:
	~CTestApp() override = default;

public:
	static CTestApp* GetInstance() noexcept;

public:
	virtual void Init(
		const UINT& width,
		const UINT& height,
		const wchar_t* className,
		const wchar_t* applicaitonName
	) noexcept override;
	virtual void Update(const float& deltaTime) override;
	virtual void Quit() override;
	virtual void AppProcImpl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

};


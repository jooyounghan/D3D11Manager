#pragma once
#ifndef BASEAPP_H
#define BASEAPE_H

#include "D3D11DllHelper.h"

#include <Windows.h>
#include <functional>

namespace D3D11
{
	using WndSizeUpdateHandler = std::function<void(const UINT& width, const UINT& height)>;

	class D3D11MANAGER_API CBaseApp
	{
	protected:
		CBaseApp() noexcept;
		CBaseApp(const CBaseApp& baseApp) = delete;
		CBaseApp(CBaseApp&& baseApp) = delete;

	public:
		virtual ~CBaseApp() = default;

	public:
		static CBaseApp* MainApp;

	protected:
		WNDCLASSEX m_windowClass;
		HWND m_mainWindow = NULL;

	public:
		inline HWND GetWindowHandle() const noexcept { return m_mainWindow; }

	protected:
		UINT m_width = 0;
		UINT m_height = 0;

	public:
		inline const UINT& GetWidth() const noexcept { return m_width; }
		inline const UINT& GetHeight() const noexcept { return m_height; }

	protected:
		LARGE_INTEGER m_frequency;
		LARGE_INTEGER m_prevTime;

	protected:
		WndSizeUpdateHandler m_wndSizeUpdateHandler = [&](const UINT&, const UINT&) {};

	public:
		void Run();

	public:
		LRESULT WINAPI AppProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		virtual void Init(
			const UINT& width,
			const UINT& height,
			const wchar_t* className,
			const wchar_t* applicaitonName
		) noexcept;

	public:
		virtual void Update(const float& deltaTime) = 0;
		virtual void Quit() = 0;
		virtual void AppProcImpl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	private:
		void OnWindowSizeMove() noexcept;
		float GetDeltaTime() noexcept;
	};
}
#endif
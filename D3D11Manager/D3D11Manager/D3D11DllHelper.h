#pragma once

namespace D3D11
{
	#ifdef D3D11MANAGER_EXPORTS
	#define D3D11MANAGER_API __declspec(dllexport)
	#else
	#define D3D11MANAGER_API __declspec(dllimport)
	#endif
}
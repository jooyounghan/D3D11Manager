#pragma once

#ifndef DEPTHSTENCILSTATE_H
#define DEPTHSTENCILSTATE_H

#include "D3D11DllHelper.h"

#include <d3d11.h>
#include <wrl/client.h>
#include <float.h>

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11SamplerState>;

namespace D3D11
{
	class D3D11MANAGER_API SamplerState
	{
	public:
		SamplerState(
			ID3D11Device* device,
			D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
			D3D11_TEXTURE_ADDRESS_MODE addressU = D3D11_TEXTURE_ADDRESS_CLAMP,
			D3D11_TEXTURE_ADDRESS_MODE addressV = D3D11_TEXTURE_ADDRESS_CLAMP,
			D3D11_TEXTURE_ADDRESS_MODE addressW = D3D11_TEXTURE_ADDRESS_CLAMP,
			FLOAT mipLODBias = 0,
			UINT maxAnisotropy = 1,
			D3D11_COMPARISON_FUNC comparisonFunc = D3D11_COMPARISON_NEVER,
			const FLOAT* borderColor = nullptr,
			FLOAT minLOD = -FLT_MAX,
			FLOAT maxLOD = FLT_MAX
		);
		~SamplerState() = default;

	private:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;

	public:
		inline ID3D11SamplerState* GetSS() const noexcept { return m_samplerState.Get(); }

	public:
		static void InitializeSamplerState(ID3D11Device* device);

	private:
		static Microsoft::WRL::ComPtr<ID3D11SamplerState> gSSWrap;
		static Microsoft::WRL::ComPtr<ID3D11SamplerState> gSSClamp;
		static Microsoft::WRL::ComPtr<ID3D11SamplerState> gSSWrapLess;
		static Microsoft::WRL::ComPtr<ID3D11SamplerState> gSSClampLess;

	};
}

#endif
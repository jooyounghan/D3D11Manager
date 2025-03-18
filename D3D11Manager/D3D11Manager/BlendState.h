#pragma once

#ifndef BLENDSTATE_H
#define BLENDSTATE_H

#include "D3D11DllHelper.h"

#include <d3d11.h>
#include <wrl/client.h>

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11BlendState>;

namespace D3D11
{
	class D3D11MANAGER_API CBlendState
	{
	public:
		CBlendState(
			ID3D11Device* device,
			BOOL alphaToCoverageEnable,
			UINT renderTargetBlendDescCount,
			D3D11_RENDER_TARGET_BLEND_DESC* renderTargetBlendDescs
		);
		~CBlendState() = default;

	private:
		Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;

	public:
		inline ID3D11BlendState* GetRS() const noexcept { return m_blendState.Get(); }

	private:
		static void InitializeDefaultBlendStates(ID3D11Device* device);

	private:
		static Microsoft::WRL::ComPtr<ID3D11BlendState> gBSAccumulateSS;
		static Microsoft::WRL::ComPtr<ID3D11BlendState> gBSAccumulateMS;
	};
}
#endif
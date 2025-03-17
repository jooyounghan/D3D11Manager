#pragma once

#ifndef COMPUTESHADER_H
#define COMPUTESHADER_H

#include "AShader.h"

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11ComputeShader>;

namespace D3D11
{
	class D3D11MANAGER_API ComputeShader : public AShader
	{
	public:
		ComputeShader() = default;
		virtual ~ComputeShader() = default;


	protected:
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_computeShader;

	protected:
		virtual void CreateShaderImpl(ID3D11Device* device) override;

	public:
		virtual void SetShader(ID3D11DeviceContext* deviceContext) const noexcept override;
		virtual void ResetShader(ID3D11DeviceContext* deviceContext) const noexcept override;
		virtual void SetSamplerState(
			ID3D11DeviceContext* deviceContext,
			const std::vector<ID3D11SamplerState*>& samplerStates
		)  noexcept override;
		virtual void ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept override;

	};
}

#endif


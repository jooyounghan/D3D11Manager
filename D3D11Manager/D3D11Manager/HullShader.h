#pragma once

#ifndef HULLSHADER_H
#define HULLSHADER_H

#include "AShader.h"

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11HullShader>;

namespace D3D11
{
	class D3D11MANAGER_API HullShader : public AShader
	{
	public:
		HullShader() = default;
		virtual ~HullShader() = default;


	protected:
		Microsoft::WRL::ComPtr<ID3D11HullShader> m_hullShader;

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

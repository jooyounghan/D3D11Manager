#pragma once

#ifndef DOMAINSHADER_H
#define DOMAINSHADER_H

#include "AShader.h"

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11DomainShader>;

namespace D3D11
{
	class D3D11MANAGER_API DomainShader : public AShader
	{
	public:
		DomainShader() = default;
		virtual ~DomainShader() = default;


	protected:
		Microsoft::WRL::ComPtr<ID3D11DomainShader> m_domainShader;

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
#pragma once

#ifndef GEOMETRYSHADER_H
#define GEOMETRYSHADER_H

#include "AShader.h"

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11GeometryShader>;

namespace D3D11
{
	class D3D11MANAGER_API CGeometryShader : public AShader
	{
	public:
		CGeometryShader() = default;
		~CGeometryShader() override = default;


	protected:
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

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
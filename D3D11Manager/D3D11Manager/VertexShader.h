#pragma once

#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "AShader.h"

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11VertexShader>;
template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11InputLayout>;

namespace D3D11
{
	class D3D11MANAGER_API CVertexShader : public AShader
	{
	public:
		CVertexShader(const size_t& inputLayoutCount);
		~CVertexShader() override;

	protected:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		size_t m_inputLayoutCount;
		size_t m_currentLayoutCount = 0;
		D3D11_INPUT_ELEMENT_DESC* m_inputElementDescs;
		
	protected:
		virtual void CreateShaderImpl(ID3D11Device* device) override;

	public:
		void AddInputLayoutElement(const D3D11_INPUT_ELEMENT_DESC& inputElementDesc);

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
